#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "./filtros/filtros.cpp"
#include "./transformadas/transformadas.cpp"
#include "./histograma/histograma_global.cpp"
#include "./histograma/histograma_local.cpp"
#include "./filtros_espaciais/filtros_espaciais.cpp"
#include "./deteccao_bordas/deteccao_bordas.cpp"
#include "./BIC/bic.cpp"



using namespace cv;
using namespace std;

int main() {
    Mat imagem = imread("./imagens/salaEstar.jpg", IMREAD_COLOR);
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
                    "4 - Gerar histograma local (4 Partições)\n"
                    "5 - Filtros Espacias\n"
                    "6 - Detecção de Bordas\n"
                    "7 - Extração de Propriedades de cor (BIC)"
                    "\nDigite o número da opcao: ";
    
    
    cout << opcoes;
    cin >> numero_operacao;

    if(numero_operacao ==1){

        
        /*


        FILTROS
        

        
        */


        cout << "\nEScolha o numero do filtro:\n" << "1 - Aumentar Brilho" << endl << "2 - Filtro Negativo\n" << "3 - Imagem na Escala Cinza" << endl;
        cin >> num_opcao;

        if(num_opcao == 1){
            int valor;
            cout << "\nDigite um valor a ser somado nos pixels para aumentar o brilho: ";
            cin >> valor;
            Mat imagem_brilho = aumenta_brilho(imagem, valor, "./imagens/saida/imagem_brilho_aumentado.jpg"); // Correção aqui
            imshow("Imagem Brilho Aumentado", imagem_brilho); // Mostra a imagem com brilho aumentado
            waitKey(0); // Espera a tecla ser pressionada
        }
        if(num_opcao==2){
            Mat imagem_negativa = filtro_negativo(imagem, "./imagens/saida/imagem_negativa.jpg");

            imshow("Imagem negativa", imagem_negativa);
            waitKey(0);


        }if(num_opcao==3){
            Mat imagem_cinza = filtro_escalaCinza(imagem, "./imagens/saida/imagem_escalaCinza.jpg");

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
                                     "\nDigite o numero da opcao: ";
            
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

                Mat imagem_exp_cont_linear = expansao_contraste_linear(imagem, za, zb, z1, zn, "./imagens/saida/imagem_ExpContrasteLinear.jpg");

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

                Mat imagem_compressao_expansao = compressao_expansao(imagem, "./imagens/saida/imagem_CompressaoExpansao.jpg");

                imshow("img Compressão Expansão", imagem_compressao_expansao);
                waitKey(0);
            }

            if(num_opcao==3){
                /*


                Dente de Serra
                    

                    
                */

               //REVISAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

               Mat imagem_dente_serra = dente_de_serra(imagem, "./imagens/saida/imagem_DenteSerra.jpg");

                imshow("Img Dente de Serra", imagem_dente_serra);
                waitKey(0);

            }

            if(num_opcao==4){

                /*


                Escala Logaritmica
                    

                    
                */
                int valorLog;

                cout << "\nDigite um valor para C: \n";
                cin >> valorLog;

                Mat imagem_log = escala_log(imagem, valorLog, "./imagens/saida/imagem_EscalaLog.jpg");

                imshow("Imagem log", imagem_log);
                waitKey(0);
            }
            

    }

    else if(numero_operacao==3){
        /*


            HISTOGRAMA GLOBAL
                    

                    
        */
       
        
        calcularSalvarHistogramaGlobal(imagem, "histograma_global.txt");
        return 0;


    }

    else if(numero_operacao==4){
        /*


            HISTOGRAMA LOCAL
                    

                    
        */

       calcularSalvarHistogramaLocal(imagem, "histograma_local.txt");
        return 0;
    }

    else if(numero_operacao==5){
        /*


            FILTROS ESPACIAIS
                    

                    
        */
       int num_opcao;
       imagem = imread("./imagens/imagem_com_ruido_sal_e_pimenta_colorido.png", IMREAD_COLOR);


       string op_filtros_espaciais = "\nEscolha um dos Filtros Espaciais abaixo:\n"
                                     "1 - Filtro da Média\n"
                                     "2 - Filtro dos K vizinhos mais próximos\n"
                                     "3 - Filtro da Mediana\n"
                                     "4 - Filtro da Moda\n"
                                     "\nDigite o numero da opcao: ";
        
        cout << op_filtros_espaciais;
        cin >> num_opcao;

        if(num_opcao==1){
            /*


            FILTRO DA Média
                    

                    
            */

           Mat imagem_media = filtro_da_media(imagem, "./imagens/saida/imagem_Media_salPimenta.png");

           imshow("Filtro da Média", imagem_media);
           waitKey(0);
        }

        if(num_opcao==2){
             /*


            FILTRO DO K VIZINHOS MAIS PRÓXIMOS
                    
             
            */
           
           int k;
           cout << "\nDigite um valor para o K: ";
           cin >> k;

           Mat imagem_k_vizinhos = filtro_K_Vizinhos_Proximos(imagem, k, "./imagens/saida/imagem_Kvizinhos_salPimenta.png");

           imshow("Filtro K vizinhos mais próximos", imagem_k_vizinhos);
           waitKey(0);
        }

        if(num_opcao==3){
            /*


            FILTRO DA MEDIANA
                    
             
            */
           

           Mat imagem_mediana = filtro_mediana(imagem, "./imagens/saida/imagem_Mediana_salPimenta.png");


           imshow("Filtro da Mediana", imagem_mediana);
           waitKey(0);

        }

        if(num_opcao==4){
            
            //Revisar o código, ou encontrar uma imagem que seja boa para teste este filtro!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            Mat imagem_moda = filtro_moda(imagem, "./imagens/saida/imagem_Moda_salPimenta.png");


           imshow("Filtro da Moda", imagem_moda);
           waitKey(0);
        }
    }

    else if(numero_operacao==6){
        /*


            DETECÇÃO DE BORDAS
                    

                    
        */

        imagem = imread("./imagens/salaEstar.jpg", IMREAD_COLOR);
        // Reduz a quantização de cores para 32 cores
        //Mat imagemQuantizada = reduzirQuantizacaoCores(imagem, 32);

        // Aplica o filtro de Roberts na imagem quantizada
        Mat imagemFiltrada = filtro_roberts(imagem, "./imagens/saida/imagem_filtrada_roberts.jpg");

        // Exibir a imagem original e a filtrada
        //imshow("Imagem Original", imagem);
        imshow("Imagem Filtrada - Filtro de Roberts", imagemFiltrada);
        waitKey(0);
    }

    else if(numero_operacao==7){
        /*


            EXTRAÇÃO DE PROPRIEDADES DE COR
                    

                    
        */
        // Carregar a imagem
        Mat imagemOriginal = imread("./imagens/salaEstar.jpg");
        if (imagemOriginal.empty()) {
            cerr << "Erro ao carregar a imagem." << endl;
            return -1;
        }

        // Executar a extração de propriedades de cor
        extrairPropriedadesCor(imagemOriginal, 64, "./imagens/saida");


    }
    
    return 0;
}


