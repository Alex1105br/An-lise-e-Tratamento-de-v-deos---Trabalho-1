#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;


void calcularSalvarHistogramaLocal(const Mat& imagem, const string& nomeArquivo) {
    // Obter as dimensões da imagem
    int altura = imagem.rows;
    int largura = imagem.cols;

    // Definir os limites das 4 partições
    Rect particoes[4] = {
        Rect(0, 0, largura / 2, altura / 2),         // 1ª Partição: superior esquerdo
        Rect(largura / 2, 0, largura / 2, altura / 2), // 2ª Partição: superior direito
        Rect(0, altura / 2, largura / 2, altura / 2),  // 3ª Partição: inferior esquerdo
        Rect(largura / 2, altura / 2, largura / 2, altura / 2)  // 4ª Partição: inferior direito
    };

    // Vetores para armazenar os histogramas de cada partição
    Mat b_hist, g_hist, r_hist;
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};

    // Abrir o arquivo para salvar o histograma
    ofstream arquivo(nomeArquivo);

    // Loop para calcular o histograma de cada partição
    for (int p = 0; p < 4; ++p) {
        // Recortar a partição atual da imagem
        Mat particao = imagem(particoes[p]);

        // Dividir a partição nos canais B, G, R
        vector<Mat> canais;
        split(particao, canais);

        // Calcular o histograma para cada canal (Azul, Verde e Vermelho)
        calcHist(&canais[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, true, false);
        calcHist(&canais[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, true, false);
        calcHist(&canais[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, true, false);

        // Escrever a partição atual no arquivo
        arquivo << (p + 1) << "ª PARTIÇÃO\n\n";

        // Canal Azul
        arquivo << "CANAL AZUL\n\n";
        for (int i = 0; i < histSize; ++i) {
            arquivo << "Intensidade " << i << ": " << b_hist.at<float>(i) << " pixels\n";
        }
        arquivo << "\n";

        // Canal Verde
        arquivo << "CANAL VERDE\n\n";
        for (int i = 0; i < histSize; ++i) {
            arquivo << "Intensidade " << i << ": " << g_hist.at<float>(i) << " pixels\n";
        }
        arquivo << "\n";

        // Canal Vermelho
        arquivo << "CANAL VERMELHO\n\n";
        for (int i = 0; i < histSize; ++i) {
            arquivo << "Intensidade " << i << ": " << r_hist.at<float>(i) << " pixels\n";
        }
        arquivo << "\n";
    }

    // Fechar o arquivo
    arquivo.close();

    cout << "Histograma local armazenado em '" << nomeArquivo << endl;
}
