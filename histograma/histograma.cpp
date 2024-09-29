#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void gerarHistograma(const Mat& img_original) {
    // Verifica se a imagem está em escala de cinza ou colorida
    bool imagemColorida = (img_original.channels() == 3);

    vector<Mat> canais;
    
    // Se for uma imagem colorida, separamos os 3 canais (B, G, R)
    if (imagemColorida) {
        split(img_original, canais);
    } else {
        // Caso contrário, apenas usamos a imagem como escala de cinza
        canais.push_back(img_original);
    }

    // Parâmetros do histograma
    int histSize = 256;        // Número de níveis de intensidade (0-255)
    float range[] = { 0, 256 }; // Faixa de intensidade (0-255)
    const float* histRange = { range };

    bool uniform = true, accumulate = false;
    Mat histB, histG, histR, histGray;

    // Calcula o histograma para a imagem em escala de cinza ou para cada canal de cor
    if (imagemColorida) {
        calcHist(&canais[0], 1, 0, Mat(), histB, 1, &histSize, &histRange, uniform, accumulate); // Canal azul
        calcHist(&canais[1], 1, 0, Mat(), histG, 1, &histSize, &histRange, uniform, accumulate); // Canal verde
        calcHist(&canais[2], 1, 0, Mat(), histR, 1, &histSize, &histRange, uniform, accumulate); // Canal vermelho
    } else {
        calcHist(&canais[0], 1, 0, Mat(), histGray, 1, &histSize, &histRange, uniform, accumulate); // Escala de cinza
    }

    // Normaliza o histograma para que caiba no tamanho da janela
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    if (imagemColorida) {
        normalize(histB, histB, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(histG, histG, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(histR, histR, 0, histImage.rows, NORM_MINMAX, -1, Mat());

        // Desenha o histograma para os 3 canais de cores
        for (int i = 1; i < histSize; i++) {
            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histB.at<float>(i - 1))),
                 Point(bin_w * (i), hist_h - cvRound(histB.at<float>(i))),
                 Scalar(255, 0, 0), 2, 8, 0); // Azul

            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histG.at<float>(i - 1))),
                 Point(bin_w * (i), hist_h - cvRound(histG.at<float>(i))),
                 Scalar(0, 255, 0), 2, 8, 0); // Verde

            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histR.at<float>(i - 1))),
                 Point(bin_w * (i), hist_h - cvRound(histR.at<float>(i))),
                 Scalar(0, 0, 255), 2, 8, 0); // Vermelho
        }
    } else {
        normalize(histGray, histGray, 0, histImage.rows, NORM_MINMAX, -1, Mat());

        // Desenha o histograma para a imagem em escala de cinza
        for (int i = 1; i < histSize; i++) {
            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histGray.at<float>(i - 1))),
                 Point(bin_w * (i), hist_h - cvRound(histGray.at<float>(i))),
                 Scalar(255, 255, 255), 2, 8, 0); // Escala de cinza (branco)
        }
    }

    // Exibe o histograma
    imshow("Histograma", histImage);
    waitKey(0);
}

int main() {
    // Carrega a imagem
    Mat imagem = imread("londres.jpg", IMREAD_COLOR);

    if (imagem.empty()) {
        cout << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    // Gera o histograma
    gerarHistograma(imagem);

    return 0;
}
