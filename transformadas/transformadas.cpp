#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;



Mat escala_log(const Mat& img_original, int valorC){
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;


    for(int x = 0; x < altura; x++){
        for(int y = 0; y < largura; y++){
            Vec3b& pixel = img.at<Vec3b>(x, y);

            //int valorLog = valorC * (1+pixel[0]+pixel[1]+pixel[2]);

            // Limita os valores dos canais a 255, se ultrapassarem
            pixel[0] = valorC * (log(1+pixel[0])); 
            pixel[1] = valorC * (log(1+pixel[1])); 
            pixel[2] = valorC * (log(1+pixel[2])); 
        }
    }

    return img;
}




Mat expansao_contraste_linear(const Mat& img_original, int za, int zb, int z1, int zn) {
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {

            // Acessando o pixel da imagem original
            Vec3b pixel_original = img_original.at<Vec3b>(i, j);
            Vec3b& pixel_modificado = img.at<Vec3b>(i, j);

            // Iterando sobre os três canais de cor (B, G, R)
            for (int canal = 0; canal < 3; canal++) {
                if (pixel_original[canal] <= za) {
                    pixel_modificado[canal] = z1;
                }
                else if (pixel_original[canal] > za && pixel_original[canal] < zb) {
                    pixel_modificado[canal] = round(((zn - z1) / (float)(zb - za)) * (pixel_original[canal] - za) + z1);
                }
                else if (pixel_original[canal] >= zb) {
                    pixel_modificado[canal] = zn;
                }
            }
        }
    }

    return img;
}








Mat expansao_contraste_linear2(const Mat& img_original, int za, int zb, int z1, int zn) {
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    for (int x = 0; x < altura; x++) {
        for (int y = 0; y < largura; y++) {
            Vec3b& pixel = img.at<Vec3b>(x, y);

            for (int c = 0; c < 3; c++) { // Itera sobre os canais de cor
                if (img_original.at<Vec3b>(x, y)[c] <= za) {
                    pixel[c] = z1;
                } else if (img_original.at<Vec3b>(x, y)[c] > za && img_original.at<Vec3b>(x, y)[c] < zb) {
                    pixel[c] = round(((zn - z1) / (zb - za)) * (img_original.at<Vec3b>(x, y)[c] - za) + z1);
                } else if (img_original.at<Vec3b>(x, y)[c] >= zb) {
                    pixel[c] = zn;
                }
            }
        }
    }

    return img;
}


Mat compressao_expansao(const Mat& img_original){
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    for(int i =0; i<altura;i++){
        for(int j=0; j<largura; j++){
            Vec3b pixel_original = img_original.at<Vec3b>(i, j);
            Vec3b& pixel_modificado = img.at<Vec3b>(i, j);

            // Iterando sobre os três canais de cor (B, G, R)
            for (int canal = 0; canal < 3; canal++) {

                if (pixel_original[canal] <= 85) {
                    pixel_modificado[canal] = pixel_original[canal]/2;
                }

                else if (pixel_original[canal] > 75 && pixel_original[canal] < 170) {
                    pixel_modificado[canal] = 2* pixel_original[canal] - 127;
                }

                else if (pixel_original[canal] >= 170) {
                    pixel_modificado[canal] = (pixel_original[canal]/2) + 128;
                }
            }


        }
    }

    return img;
}


Mat dente_de_serra(const Mat& img_original) {
    // Clonar a imagem original para evitar alterações diretas nela
    Mat img = img_original.clone();

    // Obter as dimensões da imagem
    int altura = img_original.rows;
    int largura = img_original.cols;

    // Aplicar a transformação do dente de serra para cada pixel da imagem
    for (int i = 0; i < altura; i++) { // Itera sobre as linhas
        for (int j = 0; j < largura; j++) { // Itera sobre as colunas
            Vec3b& pixel_modificado = img.at<Vec3b>(i, j); // Pixel modificado

            // Iterar sobre os três canais de cor (B, G, R)
            for (int canal = 0; canal < 3; canal++) {
                if (pixel_modificado[canal] < 63) {
                    pixel_modificado[canal] = static_cast<int>(255 * pixel_modificado[canal] / 62.0);// o static_cast nesta linha está convertendo o valor para inteiro, o mesmo para as outras linhas
                } 
                else if (pixel_modificado[canal] < 127) {
                    pixel_modificado[canal] = static_cast<int>(255 * (pixel_modificado[canal] - 63) / 63.0);
                } 
                else if (pixel_modificado[canal] < 191) {
                    pixel_modificado[canal] = static_cast<int>(255 * (pixel_modificado[canal] - 127) / 63.0);
                } 
                else {
                    pixel_modificado[canal] = static_cast<int>(255 * (pixel_modificado[canal] - 191) / 64.0);
                }
            }
        }
    }

    return img;
}
