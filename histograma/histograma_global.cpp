#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;


void calcularSalvarHistogramaGlobal(const Mat& imagem, const string& nomeArquivo) {
    // Divide a imagem nos canais B, G e R
    vector<Mat> canais;
    split(imagem, canais);

    // Parâmetros do histograma
    int histSize = 256; // Número de bins
    float range[] = {0, 256}; // Intervalo de valores
    const float* histRange = {range};

    // Vetores para armazenar os histogramas
    Mat b_hist, g_hist, r_hist;

    // Calcula os histogramas para cada canal
    calcHist(&canais[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, true, false);
    calcHist(&canais[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, true, false);
    calcHist(&canais[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, true, false);

    // Armazena o histograma formatado em um arquivo texto
    ofstream arquivo(nomeArquivo);
    

    // Salvando o histograma do canal Azul
    arquivo << "CANAL AZUL\n\n\n";
    for (int i = 0; i < histSize; ++i) {
        arquivo << "Intensidade " << i << ": " << b_hist.at<float>(i) << " pixels\n";
        
    }
    arquivo << "\n"; // Nova linha para separar as bandas

    // Salvando o histograma do canal Verde
    arquivo << "\nCANAL VERDE\n\n\n";
    for (int i = 0; i < histSize; ++i) {
        arquivo << "Intensidade " << i << ": " << g_hist.at<float>(i) << " pixels\n";
        
    }
    arquivo << "\n"; // Nova linha para separar as bandas

    // Salvando o histograma do canal Vermelho
    arquivo << "\nCANAL VERMELHO\n\n\n";
    for (int i = 0; i < histSize; ++i) {
        arquivo << "Intensidade " << i << ": " << r_hist.at<float>(i) << " pixels\n";
        
    }
   

    arquivo.close();
    cout << "Histograma global armazenado em '" << nomeArquivo << endl;
}



