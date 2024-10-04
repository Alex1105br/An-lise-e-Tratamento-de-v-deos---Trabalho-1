#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace cv;
using namespace std;

Mat filtro_da_media(const Mat& imgOriginal, const std::string& caminhoSalvar) {
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
                        if (novoI >= 0 && novoJ >= 0 && novoI < altura && novoJ < largura) {
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

    // Salvar a imagem no caminho especificado
    if (!imwrite(caminhoSalvar, img)) {
        cerr << "Erro ao salvar a imagem em: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
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

// Função para obter os vizinhos de um pixel com uma janela 5x5
vector<int> obterVizinhos_5x5(const Mat& img, int i, int j, int canal) {
    vector<int> vetor_k;

    // Definir as posições relativas dos 24 vizinhos em uma janela 5x5
    int dx[] = {-2, -2, -2, -2, -2, -1, -1, -1, -1, -1, 0,  0,  0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
    int dy[] = {-2, -1,  0,  1,  2, -2, -1,  0,  1,  2, -2, -1, 1, 2, 0, -2, -1, 0, 1, 2, -2, -1, 0, 1, 2};

    // Iterar sobre os 24 vizinhos
    for (int k = 0; k < 25; k++) {
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


Mat filtro_K_Vizinhos_Proximos(const Mat& imgOriginal, int k, const std::string& caminhoSalvar) {
    // Copiar a imagem original
    Mat img = imgOriginal.clone();

    // Obter as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    // Iterar sobre os pixels da imagem
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            Vec3b& pixelCentral = img.at<Vec3b>(i, j); // Referência ao pixel central

            // Iterar sobre os canais de cor (B, G, R)
            for (int canal = 0; canal < 3; canal++) {
                // Obter os vizinhos do pixel central
                vector<int> vizinhos = obterVizinhos(img, i, j, canal);

                // Ordenar e limitar ao valor de k vizinhos
                if (vizinhos.size() > k) {
                    sort(vizinhos.begin(), vizinhos.end());
                    vizinhos.resize(k);
                }

                // Calcular a média dos k vizinhos mais próximos
                int soma_k_proximos = std::accumulate(vizinhos.begin(), vizinhos.end(), 0);
                int media_k = (pixelCentral[canal] + soma_k_proximos) / (vizinhos.size() + 1);
                pixelCentral[canal] = saturate_cast<uchar>(media_k);
            }
        }
    }

    // Salvar a imagem no caminho especificado
    if (!imwrite(caminhoSalvar, img)) {
        cerr << "Erro ao salvar a imagem em: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
    }

    return img;
}





// Função para calcular a mediana de um vetor
int calcularMediana(vector<int>& vetor) {
    // Ordenar o vetor
    sort(vetor.begin(), vetor.end());

    // Calcular a mediana
    int mediana;
    size_t tamanho = vetor.size();
    if (tamanho % 2 == 0) {
        // Se o tamanho for par, a mediana é a média truncada dos dois elementos do meio
        mediana = (vetor[tamanho / 2 - 1] + vetor[tamanho / 2]) / 2;
    } else {
        // Se o tamanho for ímpar, a mediana é o elemento do meio
        mediana = vetor[tamanho / 2];
    }

    return mediana;
}



Mat filtro_mediana(const Mat& imgOriginal, const std::string& caminhoSalvar) {
    // Copiar a imagem original
    Mat img = imgOriginal.clone();

    // Obter as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    // Iterar sobre os pixels da imagem
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            Vec3b& pixelCentral = img.at<Vec3b>(i, j); // Referência ao pixel central

            // Iterar sobre os canais de cor (B, G, R)
            for (int canal = 0; canal < 3; canal++) {
                // Obter os vizinhos do pixel central
                vector<int> vizinhos = obterVizinhos(img, i, j, canal);

                // Calcular a mediana dos vizinhos
                int mediana = calcularMediana(vizinhos);
                pixelCentral[canal] = mediana;
            }
        }
    }

    // Salvar a imagem no caminho especificado
    if (!imwrite(caminhoSalvar, img)) {
        cerr << "Erro ao salvar a imagem em: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
    }

    return img;
}



// Função para calcular a moda de um vetor
int calcularModa(const vector<int>& vetor) {
    unordered_map<int, int> frequencias; // Mapeia valores para suas frequências

    // Contar as frequências de cada valor no vetor
    for (int valor : vetor) {
        frequencias[valor]++;
    }

    // Encontrar o valor com a maior frequência
    int moda = vetor[0]; // Inicializa com o primeiro elemento
    int max_frequencia = 0;

    for (const auto& par : frequencias) {
        if (par.second > max_frequencia) {
            max_frequencia = par.second;
            moda = par.first;
        }
    }

    return moda;
}

Mat filtro_moda(const Mat& imgOriginal, const std::string& caminhoSalvar) {
    // Copiar a imagem original
    Mat img = imgOriginal.clone();

    // Obter as dimensões da imagem
    int altura = img.rows;
    int largura = img.cols;

    

    // Iterar sobre os pixels da imagem
    for (int i = 1; i < altura - 1; i++) {
        for (int j = 1; j < largura - 1; j++) {
            Vec3b& pixelCentral = img.at<Vec3b>(i, j); // Referência ao pixel central

            // Iterar sobre os canais de cor (B, G, R)
            for (int canal = 0; canal < 3; canal++) {
                // Obter os vizinhos do pixel central
                vector<int> vizinhos = obterVizinhos(img, i, j, canal);


                // Calcular a moda dos vizinhos
                int moda = calcularModa(vizinhos);
                pixelCentral[canal] = moda; 
            }
        }
    }

    // Salvar a imagem no caminho especificado
    if (!imwrite(caminhoSalvar, img)) {
        cerr << "Erro ao salvar a imagem em: " << caminhoSalvar << endl;
    } else {
        cout << "Imagem salva com sucesso em: " << caminhoSalvar << endl;
    }

    return img;
}
