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
    for (int i = 1; i < altura; i++) {
        for (int j = 1; j < largura; j++) {
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




#include <numeric> // Include this header for std::accumulate



// Função para obter os vizinhos de um pixel
vector<int> obterVizinhos(const Mat& img, int i, int j, int canal) {
    vector<int> vetor_k;

    // Definir as posições relativas dos 8 vizinhos
    int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    // Iterar sobre os 8 vizinhos
    for (int k = 0; k < 8; k++) {
        int novoI = i + dx[k];
        int novoJ = j + dy[k];

        // Verificar se o vizinho está dentro dos limites da imagem
        if (novoI >= 0 && novoI < img.rows && novoJ >= 0 && novoJ < img.cols) {
            // Armazenar o valor do canal correspondente do vizinho no vetor
            vetor_k.push_back(img.at<Vec3b>(novoI, novoJ)[canal]);
        }
    }

    return vetor_k; // Retorna os valores dos vizinhos
}

// Função que aplica o filtro da média usando os k vizinhos mais próximos
Mat filtro_K_Vizinhos_Proximos(const Mat& imgOriginal, int k) {
    // Copia a imagem original para evitar alterações na imagem original
    Mat img = imgOriginal.clone();

    // Obter as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    // Iterar sobre os pixels da imagem
    for (int i = 1; i < altura - 1; i++) { // Alterado para evitar acessar pixels fora dos limites
        for (int j = 1; j < largura - 1; j++) { // Alterado para evitar acessar pixels fora dos limites
            Vec3b& pixelCentral = img.at<Vec3b>(i, j); // Referência ao pixel central

            // Iterar sobre os canais de cor (B, G, R)
            for (int canal = 0; canal < 3; canal++) {
                // Obter os vizinhos do pixel central
                vector<int> vizinhos = obterVizinhos(img, i, j, canal);
                
                // Se houver menos que k vizinhos, usar apenas os disponíveis
                if (vizinhos.size() > k) {
                    sort(vizinhos.begin(), vizinhos.end()); // Ordenar os vizinhos
                    vizinhos.resize(k); // Manter apenas os k mais próximos
                }

                // Calcular a soma dos k vizinhos mais próximos
                int soma_k_proximos = std::accumulate(vizinhos.begin(), vizinhos.end(), 0); // Use std::accumulate to specify the correct function
                
                // Calcular a média dos k valores mais próximos
                int media_k = (pixelCentral[canal] + soma_k_proximos) / (vizinhos.size() + 1); // +1 para incluir o pixel central
                pixelCentral[canal] = saturate_cast<uchar>(media_k);
            }
        }
    }

    return img;
}
