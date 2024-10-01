#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "./filtros/filtros.cpp"
#include "./transformadas/transformadas.cpp"
#include "./histograma/histograma_global.cpp"
#include "./histograma/histograma_global2.cpp"
#include "./filtros_espaciais/filtros_espaciais.cpp"



using namespace cv;
using namespace std;

int main() {
    Mat imagem = imread("./imagens/londres.jpg", IMREAD_COLOR);
    if (imagem.empty()) {
        cout << "Erro ao carregar a imagem!" << endl;
        return -1;
    }
    int num_opcao;
    int numero_operacao;

    string opcoes = "O que você deseja fazer? Escolha uma das opcoes abaixo:\n"
                    "1 - Aplicar filtro\n"
                    "2 - Aplicar Transformadas Radiométricas\n"
                    "3 - Gerar histograma Global\n"
                    "4 - Gerar histograma local\n"
                    "5 - Filtros Espacias\n"
                    "Digite o número da opcao: ";
    
    
    cout << opcoes;
    cin >> numero_operacao;

    if(numero_operacao ==1){

        
        /*


        FILTROS
        

        
        */


        cout << "\nEScolha o numero do filtro:\n" << "1 - Aumentar Brilho" << endl << "2 - Filtro Negativo\n" << "3 - Imagem na Escala Cinza" <<"\n4 - Escala Logaritmica "<< endl;
        cin >> num_opcao;

        if(num_opcao == 1){
            int valor;
            cout << "Digite um valor a ser somado nos pixels para aumentar o brilho: ";
            cin >> valor;
            Mat imagem_brilho = aumenta_brilho(imagem, valor); // Correção aqui
            imshow("Imagem Brilho Aumentado", imagem_brilho); // Mostra a imagem com brilho aumentado
            waitKey(0); // Espera a tecla ser pressionada
        }
        if(num_opcao==2){
            Mat imagem_negativa = filtro_negativo(imagem);

            imshow("Imagem negativa", imagem_negativa);
            waitKey(0);


        }if(num_opcao==3){
            Mat imagem_cinza = filtro_escalaCinza(imagem);

            imshow("Imagem cinza", imagem_cinza);
            waitKey(0);
        }
    }
    else if(numero_operacao==2){

            /*


                TRANFORMADAS RADIOMÉTRICAS
                    

                    
            */


            string op_transformadas = "\nEscolha um das opcoes de transformadas radiometricas abaixo:\n"
                                     "1 - Expansao Contraste linear\n"
                                     "2 - Compressao e Expansao\n"
                                     "3 - Dente de Serra\n"
                                     "4 - Escala Logaritmica\n"
                                     "Digite o numero da opcao: ";
            
            cout << op_transformadas;
            cin >> num_opcao;
            
            if(num_opcao==1){

                /*


                Expansão Contraste Linear
                    

                    
            */

                int za,zb;

                int z1 = 0; int zn = 255;

                cout << "\nDigite um valor para za: ";
                cin >> za;

                cout << "\nDigite um valor para zb: ";
                cin >> zb;
                cout << endl;

                Mat imagem_exp_cont_linear = expansao_contraste_linear(imagem, za, zb, z1, zn);

                //Mat imagem_exp_cont_linear2 = expansao_contraste_linear2(imagem, za, zb, z1, zn);

                imshow("Img Expansão Contraste Linear", imagem_exp_cont_linear);
                waitKey(0);

                //imshow("Img Expansão Contraste Linear 2", imagem_exp_cont_linear2);
                //waitKey(0);

            }

            if(num_opcao==2){

                /*


                Compressão e Expansão
                    

                    
            */

                Mat imagem_compressao_expansao = compressao_expansao(imagem);

                imshow("img Compressão Expansão", imagem_compressao_expansao);
                waitKey(0);
            }

            if(num_opcao==3){
                /*


                Dente de Serra
                    

                    
                */

               //REVISAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

               Mat imagem_dente_serra = dente_de_serra(imagem);

                imshow("Img Dente de Serra", imagem_dente_serra);
                waitKey(0);

            }

            if(num_opcao==4){

                /*


                Escala Logaritmica
                    

                    
                */
                int valorLog;

                cout << "Digite um valor para C: \n";
                cin >> valorLog;

                Mat imagem_log = escala_log(imagem, valorLog);

                imshow("Imagem log", imagem_log);
                waitKey(0);
            }
            

    }

    else if(numero_operacao==3){
        /*


            HISTOGRAMA GLOBAL
                    

                    
        */
       
       // REVISAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        // Calcula o histograma
        vector<int> histograma;
        calcularHistograma2(imagem, histograma);

        // Salva o histograma em um arquivo texto
        salvarHistograma2(histograma, "histograma.txt");

        cout << "Histograma salvo em 'histograma.txt'" << endl;
        return 0;


    }

    else if(numero_operacao==4){
        /*


            HISTOGRAMA LOCAL
                    

                    
        */
    }

    else if(numero_operacao==5){
        /*


            FILTROS ESPACIAIS
                    

                    
        */
       int num_opcao;
       string op_filtros_espaciais = "\nEscolha um dos Filtros Espaciais abaixo:\n"
                                     "1 - Filtro da Média\n"
                                     "2 - Filtro dos K vizinhos mais próximos\n"
                                     "3 - Filtro da Mediaa\n"
                                     "4 - Filtro da Moda\n"
                                     "Digite o numero da opcao: ";
        
        cout << op_filtros_espaciais;
        cin >> num_opcao;

        if(num_opcao==1){
            /*


            FILTRO DA Média
                    

                    
            */

           Mat imagem_media = filtro_da_media(imagem);

           imshow("Filtro da Média", imagem_media);
           waitKey(0);
        }

        if(num_opcao==2){
             /*


            FILTRO DO K VIZINHOS MAIS PRÓXIMOS
                    
             
            */
           imagem = imread("./imagens/img_ruidoSal.png", IMREAD_COLOR);
           int k;
           cout << "Digite um valor para o K: ";
           cin >> k;

           Mat imagem_k_vizinhos = filtro_K_Vizinhos_Proximos(imagem, k);

           imshow("Filtro K vizinhos mais próximos", imagem_k_vizinhos);
           waitKey(0);
        }
    }

    else if(numero_operacao==6){
        /*


            DETECÇÃO DE BORDAS
                    

                    
        */
    }

    else if(numero_operacao==7){
        /*


            EXTRAÇÃO DE PROPRIEDADES DE COR
                    

                    
        */
    }
    
    return 0;
}


