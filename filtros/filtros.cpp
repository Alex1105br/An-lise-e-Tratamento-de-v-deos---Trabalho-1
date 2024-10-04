#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>


using namespace cv;
using namespace std;

Mat filtro_negativo(const Mat& img_original, const std::string& caminhoSalvar) {
    // Copia a imagem original para evitar alterações na imagem original
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    int cor_negativa = 255;
    for (int x = 0; x < altura; x++) {
        for (int y = 0; y < largura; y++) {
            // Acessa o pixel na posição (x, y)
            Vec3b& pixel = img.at<Vec3b>(x, y);

            // Aplica o filtro negativo
            pixel[0] = cor_negativa - pixel[0]; // Canal azul
            pixel[1] = cor_negativa - pixel[1]; // Canal verde
            pixel[2] = cor_negativa - pixel[2]; // Canal vermelho
        }
    }

    // Salva a imagem resultante no diretório especificado
    if (!imwrite(caminhoSalvar, img)) {
        cerr << "Erro ao salvar a imagem no caminho: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
    }

    return img;
}


Mat filtro_escalaCinza(const Mat& img_original, const std::string& caminhoSalvar) {
    // Copia a imagem original para evitar alterações na imagem original
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    for (int x = 0; x < altura; x++) {
        for (int y = 0; y < largura; y++) {
            Vec3b& pixel = img.at<Vec3b>(x, y); // Acessando os valores dos pixels na imagem

            int cinza = pixel[0] * 0.2126 + pixel[1] * 0.7152 + pixel[2] * 0.0722;

            pixel[0] = cinza;
            pixel[1] = cinza;
            pixel[2] = cinza;  
        }
    }

    // Salva a imagem resultante no diretório especificado
    if (!imwrite(caminhoSalvar, img)) {
        cerr << "Erro ao salvar a imagem no caminho: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
    }

    return img;
}


Mat aumenta_brilho(const Mat& img_original, int valorBrilho){
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    for(int x = 0; x < altura; x++){
        for(int y = 0; y < largura; y++){
            Vec3b& pixel = img.at<Vec3b>(x, y);

            // Limita os valores dos canais a 255, se ultrapassarem
            pixel[0] = std::min(pixel[0] + valorBrilho, 255); // Canal azul
            pixel[1] = std::min(pixel[1] + valorBrilho, 255); // Canal verde
            pixel[2] = std::min(pixel[2] + valorBrilho, 255); // Canal vermelho
        }
    }

    return img;
}

Mat aumenta_brilho(const Mat& img_original, int valorBrilho, const std::string& caminhoSalvar) {
    Mat img = img_original.clone();

    // Obtém as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    for (int x = 0; x < altura; x++) {
        for (int y = 0; y < largura; y++) {
            Vec3b& pixel = img.at<Vec3b>(x, y);

            // Limita os valores dos canais a 255, se ultrapassarem
            pixel[0] = std::min(pixel[0] + valorBrilho, 255); // Canal azul
            pixel[1] = std::min(pixel[1] + valorBrilho, 255); // Canal verde
            pixel[2] = std::min(pixel[2] + valorBrilho, 255); // Canal vermelho
        }
    }

    // Salva a imagem resultante no diretório especificado
    if (!imwrite(caminhoSalvar, img)) {
        cerr << "Erro ao salvar a imagem no caminho: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
    }

    return img;
}
