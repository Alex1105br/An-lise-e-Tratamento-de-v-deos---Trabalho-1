#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

// Função para calcular o histograma de um canal e concatenar no vetor global
void calcular_histograma_global(const Mat& img, vector<float>& histogramaGlobal, int histSize, const float* histRange) {
    vector<Mat> canais;
    split(img, canais); // Divide a imagem nos 3 canais (B, G, R)

    Mat histB, histG, histR;
    bool uniform = true, accumulate = false;

    // Calcula o histograma para cada canal
    calcHist(&canais[0], 1, 0, Mat(), histB, 1, &histSize, &histRange, uniform, accumulate); // Canal azul
    calcHist(&canais[1], 1, 0, Mat(), histG, 1, &histSize, &histRange, uniform, accumulate); // Canal verde
    calcHist(&canais[2], 1, 0, Mat(), histR, 1, &histSize, &histRange, uniform, accumulate); // Canal vermelho

    // Normaliza os histogramas para que fiquem entre 0 e 1 (opcional)
    normalize(histB, histB, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(histR, histR, 0, 1, NORM_MINMAX, -1, Mat());

    // Concatenar os histogramas em um único vetor
    for (int i = 0; i < histSize; i++) {
        histogramaGlobal.push_back(histB.at<float>(i)); // Valores do canal azul
    }
    for (int i = 0; i < histSize; i++) {
        histogramaGlobal.push_back(histG.at<float>(i)); // Valores do canal verde
    }
    for (int i = 0; i < histSize; i++) {
        histogramaGlobal.push_back(histR.at<float>(i)); // Valores do canal vermelho
    }
}

// Função para salvar o histograma concatenado em um arquivo texto
void salvar_histograma_em_arquivo(const vector<float>& histogramaGlobal, const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        for (size_t i = 0; i < histogramaGlobal.size(); i++) {
            arquivo << histogramaGlobal[i] << endl;
        }
        arquivo.close();
        cout << "Histograma salvo em " << nomeArquivo << endl;
    } else {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    }
}


/*

int main() {
    // Carrega a imagem
    Mat imagem = imread("imagem.jpg", IMREAD_COLOR);
    if (imagem.empty()) {
        cout << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    // Parâmetros do histograma
    int histSize = 256; // Número de bins
    float range[] = { 0, 256 };
    const float* histRange = { range };

    // Vetor para armazenar o histograma global (concatenado)
    vector<float> histogramaGlobal;

    // Calcula o histograma global da imagem
    calcular_histograma_global(imagem, histogramaGlobal, histSize, histRange);

    // Salva o histograma em um arquivo texto
    salvar_histograma_em_arquivo(histogramaGlobal, "histograma_global.txt");

    return 0;
}


*/
