#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

Mat filtro_da_media(const Mat& imgOriginal) {
    // Clonar a imagem original para evitar alterações diretas nela
    Mat img = imgOriginal.clone();

    // Obter as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    // Iterar sobre os pixels da imagem
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            Vec3b& pixelCentral = img.at<Vec3b>(i, j); // Referência ao pixel central

            // Iterar sobre os canais (B, G, R)
            for (int canal = 0; canal < 3; canal++) {
                int soma = 0;
                int count = 0;

                // Iterar sobre a vizinhança 3x3
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        int novoI = i + x;
                        int novoJ = j + y;

                        // Verificar se os vizinhos estão dentro dos limites da imagem
                        if (novoI >= 0 && novoI < altura && novoJ >= 0 && novoJ < largura) {
                            soma += imgOriginal.at<Vec3b>(novoI, novoJ)[canal];
                            count++;
                        }
                    }
                }

                // Calcular a média e atribuí-la ao pixel
                int media = soma / count;
                pixelCentral[canal] = static_cast<uchar>(media);
            }
        }
    }

    return img;
}
