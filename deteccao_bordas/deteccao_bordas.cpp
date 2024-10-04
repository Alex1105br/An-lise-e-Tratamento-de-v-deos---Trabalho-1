#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

// Função para aplicar o filtro de Roberts
Mat filtro_roberts(const Mat& imagem) {
    // Cria uma cópia da imagem original para trabalhar nela
    Mat imagemOriginal = imagem.clone();

    int altura = imagemOriginal.rows;
    int largura = imagemOriginal.cols;
    int canais = imagemOriginal.channels();

    // Cria uma matriz para armazenar a imagem filtrada, com o mesmo tamanho da original
    Mat imagemFiltrada = Mat::zeros(imagemOriginal.size(), CV_32F);

    // Máscaras de Roberts
    Mat Gx = (Mat_<float>(2, 2) << 1, 0, 0, -1);
    Mat Gy = (Mat_<float>(2, 2) << 0, 1, -1, 0);

    for (int canal = 0; canal < canais; canal++) {
        for (int i = 0; i < altura - 1; i++) {
            for (int j = 0; j < largura - 1; j++) {
                Mat regiao;

                // Extraindo a região de 2x2 em torno do pixel atual
                if (canais == 1) {
                    regiao = imagemOriginal(Rect(j, i, 2, 2)); // Escala de cinza
                } else {
                    vector<Mat> canaisImagem;
                    split(imagemOriginal, canaisImagem); // Separar canais da imagem colorida
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

    return imagemFiltrada;
}


