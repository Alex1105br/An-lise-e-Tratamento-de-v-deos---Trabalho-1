#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void calcularHistograma2(const Mat& imagem, vector<int>& histograma) {
    // Inicializa o histograma com zeros
    histograma.assign(256 * 3, 0);

    // Calcula o histograma para cada banda RGB
    for (int y = 0; y < imagem.rows; y++) {
        for (int x = 0; x < imagem.cols; x++) {
            Vec3b pixel = imagem.at<Vec3b>(y, x);
            histograma[pixel[0]]++;       // Banda B
            histograma[256 + pixel[1]]++; // Banda G
            histograma[512 + pixel[2]]++; // Banda R
        }
    }
}

void salvarHistograma2(const vector<int>& histograma, const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        for (int i = 0; i < histograma.size(); i++) {
            arquivo << histograma[i] << " " << endl;
        }
        arquivo.close();
    } else {
        cerr << "Não foi possível abrir o arquivo para escrita." << endl;
    }
}

/*
int main() {
    // Carrega a imagem
    Mat imagem = imread("sua_imagem.jpg");
    if (imagem.empty()) {
        cerr << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    // Calcula o histograma
    vector<int> histograma;
    calcularHistograma(imagem, histograma);

    // Salva o histograma em um arquivo texto
    salvarHistograma(histograma, "histograma.txt");

    cout << "Histograma salvo em 'histograma.txt'" << endl;
    return 0;
}

*/
