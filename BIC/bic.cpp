#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

// Função para reduzir a quantização de cores usando K-Means
Mat reduzirQuantizacaoCores2(const Mat& imagem, int k) {
    Mat dados;
    imagem.convertTo(dados, CV_32F);
    dados = dados.reshape(1, imagem.rows * imagem.cols); // Redimensiona para uma linha

    Mat labels, centros;
    kmeans(dados, k, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0), 3, KMEANS_PP_CENTERS, centros);

    Mat novaImagem(imagem.size(), imagem.type());
    for (int i = 0; i < dados.rows; i++) {
        novaImagem.at<Vec3b>(i / imagem.cols, i % imagem.cols) = Vec3b(centros.at<float>(labels.at<int>(i), 0),
                                                                      centros.at<float>(labels.at<int>(i), 1),
                                                                      centros.at<float>(labels.at<int>(i), 2));
    }

    return novaImagem;
}

// Função para classificar pixels como borda ou interior e calcular histogramas
void classificarPixels(const Mat& imagem, Mat& imagemBorda, Mat& imagemInterior, vector<int>& histogramaBorda, vector<int>& histogramaInterior, int limiar) {
    int altura = imagem.rows;
    int largura = imagem.cols;
    imagemBorda = Mat::zeros(imagem.size(), imagem.type()); // Inicializa imagem de borda
    imagemInterior = Mat::zeros(imagem.size(), imagem.type()); // Inicializa imagem de interior

    // Inicializa os histogramas
    histogramaBorda.resize(256, 0);
    histogramaInterior.resize(256, 0);

    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            Vec3b pixelAtual = imagem.at<Vec3b>(i, j);
            bool isBorda = false;

            // Verifica os vizinhos
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue; // Ignora o pixel central
                    Vec3b pixelVizinho = imagem.at<Vec3b>(i + x, j + y);
                    if (norm(pixelAtual - pixelVizinho) > limiar) {
                        isBorda = true; // O pixel é uma borda se um vizinho tem cor diferente
                        break;
                    }
                }
                if (isBorda) break;
            }

            if (isBorda) {
                imagemBorda.at<Vec3b>(i, j) = pixelAtual; // Mantém a cor original
                histogramaBorda[pixelAtual[0]]++; // Atualiza o histograma de borda
            } else {
                imagemInterior.at<Vec3b>(i, j) = pixelAtual; // Mantém a cor original
                histogramaInterior[pixelAtual[0]]++; // Atualiza o histograma de interior
            }
        }
    }
}

// Função principal para extração de propriedades de cor usando o descritor BIC
void extrairPropriedadesCor(const Mat& imagemOriginal, int k, const string& caminhoSalvar) {
    // Reduzir a quantização de cores
    Mat imagemQuantizada = reduzirQuantizacaoCores2(imagemOriginal, k);

    // Imagens para borda e interior
    Mat imagemBorda, imagemInterior;
    vector<int> histogramaBorda, histogramaInterior;

    // Classifica os pixels e calcula os histogramas
    classificarPixels(imagemQuantizada, imagemBorda, imagemInterior, histogramaBorda, histogramaInterior, 30); // limiar de 30

    // Salvar os histogramas em um arquivo
    ofstream arquivoHistograma(caminhoSalvar + "/histogramas_bic.txt");
    if (arquivoHistograma.is_open()) {
        arquivoHistograma << "--------------------------Histograma de Borda--------------------------\n\n";
        for (int i = 0; i < histogramaBorda.size(); i++) {
            arquivoHistograma<< "Pixel de intensidade " << i << ": " << histogramaBorda[i] << " pixels"<<"\n";
        }

        arquivoHistograma << "\n\n--------------------------Histograma de Interior--------------------------\n\n";
        for (int i = 0; i < histogramaInterior.size(); i++) {
            arquivoHistograma << "Pixel de intensidade " << i << ": " << histogramaInterior[i] << " pixels"<< "\n";
        }
        arquivoHistograma.close();
    } else {
        cerr << "Erro ao abrir arquivo para salvar histogramas." << endl;
    }

    // Salvar as imagens de borda e interior
    imwrite(caminhoSalvar + "/imagem_borda_bic.png", imagemBorda);
    imwrite(caminhoSalvar + "/imagem_interior_bic.png", imagemInterior);

    cout << "Histogramas e imagens salvos em: " << caminhoSalvar << endl;
}


