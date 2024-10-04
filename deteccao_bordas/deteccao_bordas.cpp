#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;



// Função para reduzir a quantização de cores usando K-Means
Mat reduzirQuantizacaoCores(const Mat& imagem, int k) {
    Mat dados;
    imagem.convertTo(dados, CV_32F);
    dados = dados.reshape(1, imagem.rows * imagem.cols);

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



Mat filtro_roberts(const Mat& imagem, const std::string& caminhoSalvar) {
    // Cria uma cópia da imagem original para trabalhar nela
    Mat imagemOriginal = imagem.clone();

    // Reduz a quantização de cores para 32 cores usando K-means
    Mat imagemReduzida = reduzirQuantizacaoCores(imagemOriginal, 32);

    int altura = imagemReduzida.rows;
    int largura = imagemReduzida.cols;
    int canais = imagemReduzida.channels();

    // Cria uma matriz para armazenar a imagem filtrada, com o mesmo tamanho da original
    Mat imagemFiltrada = Mat::zeros(imagemReduzida.size(), CV_32F);

    // Máscaras de Roberts
    Mat Gx = (Mat_<float>(2, 2) << 1, 0, 0, -1);
    Mat Gy = (Mat_<float>(2, 2) << 0, 1, -1, 0);

    for (int canal = 0; canal < canais; canal++) {
        for (int i = 0; i < altura - 1; i++) {
            for (int j = 0; j < largura - 1; j++) {
                Mat regiao;

                // Extraindo a região de 2x2 em torno do pixel atual
                if (canais == 1) {
                    regiao = imagemReduzida(Rect(j, i, 2, 2)); // Escala de cinza
                } else {
                    vector<Mat> canaisImagem;
                    split(imagemReduzida, canaisImagem); // Separar canais da imagem colorida
                    regiao = canaisImagem[canal](Rect(j, i, 2, 2)); // Canal específico
                }

                // Converter a região para float para realizar a multiplicação
                Mat regiaoFloat;
                regiao.convertTo(regiaoFloat, CV_32F);

                // Cálculo de Gx e Gy
                float gx = sum(Gx.mul(regiaoFloat))[0]; // Produto da máscara Gx pela região
                float gy = sum(Gy.mul(regiaoFloat))[0]; // Produto da máscara Gy pela região

                // Gradiente de Roberts
                float gradiente = sqrt(gx * gx + gy * gy);

                if (canais == 1) {
                    imagemFiltrada.at<float>(i, j) = gradiente; // Atualiza valor em escala de cinza
                } else {
                    imagemFiltrada.at<float>(i, j) += gradiente; // Soma o gradiente por canal
                }
            }
        }
    }

    // Normalização para que os valores fiquem entre 0 e 255
    double minVal, maxVal;
    minMaxLoc(imagemFiltrada, &minVal, &maxVal);
    imagemFiltrada.convertTo(imagemFiltrada, CV_8U, 255.0 / maxVal);

<<<<<<< HEAD
    // Salva a imagem resultante no diretório especificado
    if (!imwrite(caminhoSalvar, imagemFiltrada)) {
        cerr << "Erro ao salvar a imagem no caminho: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
    }

    return imagemFiltrada;
}


=======
    return imagemFiltrada;
    
}
>>>>>>> a7693e5f44cca8ff8afbb6faa71c32fd7c2c922e
