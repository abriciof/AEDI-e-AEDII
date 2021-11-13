/*--------------------------------------------------

    UFAM - UNIVERSIDADE FEDERAL DO AMAZONAS

ALUNO: FABRICIO DA COSTA GUIMARAES
MATRICULA: 21950515
DISCIPLINA: ALGORITMOS E ESTRUTURAS DE DADOS II
PERIODO: ESPECIAL ERE/2020
PROFESSOR: EDSON NASCIMENTO

----------------------------------------------------*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM_MAX 1000
#define BUBBLESORT 1
#define QUICKSORT 2
#define HEAPSORT 3
#define MERGESORT 4



// ######################## ESTRUTURAS #############################

typedef struct informacoes TInfo;
struct informacoes{
    int trocas;
    int comparacoes;
    int mediaTrocas;
    int mediaComparacoes;
    clock_t tempoInicial;
    clock_t tempoFinal;
    double diferenca;
    double mediaTempo;
};

TInfo *criarInfo(){
    TInfo *info = malloc(sizeof(TInfo));
    info->trocas = 0;
    info->comparacoes = 0;
    info->tempoInicial = 0;
    info->mediaTrocas = 0;
    info->mediaComparacoes = 0;
    info->tempoFinal = 0;
    info->diferenca = 0;
    info->mediaTempo = 0;
    return info;
}




// ######################## FUNCOES VETORES ########################

// Troca de elementos do mesmo vetor
int trocar(int vet[], int i, int j){
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j]=aux;
    return 1;
}

// Cria um vetor desodernado
void Vetor_Random(int vet[]){
    for(int i=0; i<TAM_MAX; i++ ) vet[i] = rand()*3; 
}

// Cria um vetor Inservamente Ordenado
void Vetor_Inverso(int vet[]){
    for(int i=0; i<TAM_MAX; i++ ) vet[i] = TAM_MAX-i-1;
}

// cria um vetor Ordenado
void Vetor_Ordenado(int vet[]){
    for(int i=0; i<TAM_MAX; i++ ) vet[i] = i;
}


// Exibe um vetor recursivamente
void printarV(int vet[], int inicio, int tam){
    if(inicio < tam){
        printf("%d ", vet[inicio]);
        printarV(vet, inicio+1, tam);
    }

}




// ########################### BUBBLESORT ############################

// Ordena recursivamente usando o bolha
void bubbleSort(int vetor[], int tam, TInfo *InfoBubble){ 
    if (tam == 1)
        return; 
  
    for (int i=0; i<tam-1; i++){
        InfoBubble->comparacoes++;
        if (vetor[i] > vetor[i+1]) 
            InfoBubble->trocas++;
            trocar(vetor, i, i+1); 
    }

    bubbleSort(vetor, tam-1, InfoBubble); 
} 






// ############################## QUICKSORT ###########################

// retorna o indice da extremidade da particao nova
int particao (int vetor[], int bot, int top, TInfo *InfoQuick){  
    int i = (bot - 1); 
    int pivo = vetor[top]; 

    for (int j = bot; j <= top - 1; j++){  
        InfoQuick->comparacoes++;
        if (vetor[j] < pivo){  
            i++;
            InfoQuick->trocas++;
            trocar(vetor, i, j);
        }  
    }  
    InfoQuick->trocas++;
    trocar(vetor, i+1, top);
    return (i + 1);  
}  
  
// recursivo QuickSort
void quickSort(int vetor[], int bot, int top, TInfo *InfoQuick){  
    InfoQuick->comparacoes++;
    if (bot < top){  
        int ind = particao(vetor, bot, top, InfoQuick);  
        quickSort(vetor, bot, ind - 1, InfoQuick);  
        quickSort(vetor, ind + 1, top, InfoQuick);  
    }  
}






// ########################## HEAPSORT ################################

// para reorganizar a heap de forma recursiva
void heapify(int vetor[], int n, int i, TInfo *InfoHeap){ 
    int maior = i;
    int esq = 2*i + 1; 
    int dir = 2*i + 2; 
  
    // se o filho esquerdo é maior que o pai
    InfoHeap->comparacoes++;
    if ((esq < n) && (vetor[esq] > vetor[maior])) 
        maior = esq; 
  
    // se o filho direito é maior que o pai 
    InfoHeap->comparacoes++;
    if (dir < n && vetor[dir] > vetor[maior]) 
        maior = dir; 
  
    // caso maior nao for a raiz
    InfoHeap->comparacoes++;
    if (maior != i){ 
        InfoHeap->trocas++;
        trocar(vetor, i, maior); 
        heapify(vetor, n, maior, InfoHeap); 
    } 
} 
  
// chama a funcao heapify
void heapSort(int vetor[], int tam, TInfo *InfoHeap){ 
    for (int i = tam / 2 - 1; i >= 0; i--) 
        heapify(vetor, tam, i, InfoHeap); 
  
    for (int i=tam-1; i>0; i--){ 
        InfoHeap->trocas++;
        trocar(vetor, 0, i);
        heapify(vetor, i, 0, InfoHeap); 
    } 
} 






// ########################## MERGESORT ################################

// intercala internamente quando chamado pela funcao mergesort
void mergeint(int vetor[], int esq, int mid, int dir, TInfo *InfoMerge){ 
    int i, j, k; 
    int n1 = mid - esq + 1; 
    int n2 = dir - mid; 
  
    int ESQ[n1], DIR[n2]; 
  
    for (i = 0; i < n1; i++) ESQ[i] = vetor[esq + i];
    for (j = 0; j < n2; j++) DIR[j] = vetor[mid + 1 + j]; 
    
  
    i = 0, j = 0, k = esq;

    while (i < n1 && j < n2) { 
        InfoMerge->comparacoes++;
        if (ESQ[i] <= DIR[j]) { 
            vetor[k] = ESQ[i]; 
            i++; 
        } 
        else { 
            InfoMerge->trocas++;
            vetor[k] = DIR[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) { 
        vetor[k] = ESQ[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) {
        vetor[k] = DIR[j]; 
        j++; 
        k++; 
    } 
} 
  
// Ordena partes de um vetor e depois intercala as partes correspondentes
void mergeSort(int vetor[], int esq, int dir, TInfo *InfoMerge){ 
    if (esq < dir) {
        int mid = esq + (dir - esq) / 2; 
        mergeSort(vetor, esq, mid, InfoMerge); 
        mergeSort(vetor, mid + 1, dir, InfoMerge); 
        mergeint(vetor, esq, mid, dir, InfoMerge); 
    } 
} 








// ######################## FUNCOES PRINCIPAIS ###########################

// Faz a media de Comparacoes, Trocas e de Tempo, para 40 vetores desordenados
void fazerMedia(int qual, TInfo *InfoOrdenacao){
    
    int vetor[TAM_MAX];

    switch (qual){
        case BUBBLESORT: // bubblesort

            for(int i=1; i<=40; i++){

                InfoOrdenacao->comparacoes = 0; // Zerando as estatisticas
                InfoOrdenacao->trocas = 0;
                InfoOrdenacao->diferenca = 0;

                Vetor_Random(vetor); // Criando um novo vetor desordenado

                InfoOrdenacao->tempoInicial = clock();
                bubbleSort(vetor, TAM_MAX, InfoOrdenacao);// Ordenacao
                InfoOrdenacao->tempoFinal = clock();

                InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;
                InfoOrdenacao->mediaTempo += InfoOrdenacao->diferenca; // Acumuladores
                InfoOrdenacao->mediaTrocas += InfoOrdenacao->trocas;
                InfoOrdenacao->mediaComparacoes += InfoOrdenacao->comparacoes;

            }
            printf("\n BUBBLESORT: ");
            break;

        case QUICKSORT: 
        
            for(int i=1; i<=40; i++){

                InfoOrdenacao->comparacoes = 0;
                InfoOrdenacao->trocas = 0;
                InfoOrdenacao->diferenca = 0;

                Vetor_Random(vetor);

                InfoOrdenacao->tempoInicial = clock();
                quickSort(vetor,0, TAM_MAX-1, InfoOrdenacao);
                InfoOrdenacao->tempoFinal = clock();

                InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;
                InfoOrdenacao->mediaTempo += InfoOrdenacao->diferenca;
                InfoOrdenacao->mediaTrocas += InfoOrdenacao->trocas;
                InfoOrdenacao->mediaComparacoes += InfoOrdenacao->comparacoes;

            }
            printf("\n QUICKSORT: ");
            break;

        case HEAPSORT:
        
            for(int i=1; i<=40; i++){

                InfoOrdenacao->comparacoes = 0;
                InfoOrdenacao->trocas = 0;
                InfoOrdenacao->diferenca = 0;

                Vetor_Random(vetor);

                InfoOrdenacao->tempoInicial = clock();
                heapSort(vetor, TAM_MAX, InfoOrdenacao);
                InfoOrdenacao->tempoFinal = clock();

                InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;
                InfoOrdenacao->mediaTempo += InfoOrdenacao->diferenca;
                InfoOrdenacao->mediaTrocas += InfoOrdenacao->trocas;
                InfoOrdenacao->mediaComparacoes += InfoOrdenacao->comparacoes;

            }
            printf("\n HEAPSORT: ");
            break;

        case MERGESORT:

            for(int i=1; i<=40; i++){

                InfoOrdenacao->comparacoes = 0;
                InfoOrdenacao->trocas = 0;
                InfoOrdenacao->diferenca = 0;

                Vetor_Random(vetor);

                InfoOrdenacao->tempoInicial = clock();
                mergeSort(vetor, 0, TAM_MAX-1, InfoOrdenacao);
                InfoOrdenacao->tempoFinal = clock();

                InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;
                InfoOrdenacao->mediaTempo += InfoOrdenacao->diferenca;
                InfoOrdenacao->mediaTrocas += InfoOrdenacao->trocas;
                InfoOrdenacao->mediaComparacoes += InfoOrdenacao->comparacoes;

            }
            printf("\n MERGESORT: ");
            break;
        
        default:
            break;

    }

    // Printagem do resultado da operacao
    InfoOrdenacao->mediaTempo = (double)(InfoOrdenacao->mediaTempo*1000)/(double)CLOCKS_PER_SEC;
    printf("\n\n Media de Comparacoes: %d\n Media de Trocas: %d", InfoOrdenacao->mediaComparacoes/40, InfoOrdenacao->mediaTrocas/40);
    printf("\n Tempo Medio: %lf ms", InfoOrdenacao->mediaTempo/40);    

    free(vetor);
 }
    

// Fazer o calculo das estatisticas para cada tipo de ordenacao (Vetor Ordenado)
void comVetorOrdenado(int qual, TInfo *InfoOrdenacao){

    int vetor[TAM_MAX];
    Vetor_Ordenado(vetor); // Criacao do vetor ordenado

    switch (qual){
        case BUBBLESORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            bubbleSort(vetor,TAM_MAX, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        case QUICKSORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            quickSort(vetor,0, TAM_MAX-1, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        case HEAPSORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            heapSort(vetor, TAM_MAX, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        case MERGESORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            mergeSort(vetor, 0, TAM_MAX-1, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        default:
            break;

    }

    // Printagem do resultado da operacao
    InfoOrdenacao->diferenca = (double)(InfoOrdenacao->diferenca*1000)/(double)CLOCKS_PER_SEC;
    printf("\n Comparacoes (Vetor Ordenado): %d \n Trocas (Vetor Ordenado): %d", InfoOrdenacao->comparacoes, InfoOrdenacao->trocas);
    printf("\n Tempo (Vetor Ordenado): %lf ms", InfoOrdenacao->diferenca);

    free(vetor);
}


// Fazer o calculo das estatisticas para cada tipo de ordenacao (Vetor Inversamente Ordenado)
void comVetorOrdenadoInversamente(int qual, TInfo *InfoOrdenacao){

    int vetor[TAM_MAX];
    Vetor_Inverso(vetor); // Criacao do vetor inversamente ordenado

    switch (qual){
        case BUBBLESORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            bubbleSort(vetor,TAM_MAX, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        case QUICKSORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            quickSort(vetor,0, TAM_MAX-1, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        case HEAPSORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            heapSort(vetor, TAM_MAX, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        case MERGESORT:

            InfoOrdenacao->comparacoes = 0;
            InfoOrdenacao->trocas = 0;
            InfoOrdenacao->diferenca = 0;

            InfoOrdenacao->tempoInicial = clock();
            mergeSort(vetor, 0, TAM_MAX-1, InfoOrdenacao);
            InfoOrdenacao->tempoFinal = clock();

            InfoOrdenacao->diferenca = (double)InfoOrdenacao->tempoFinal - (double)InfoOrdenacao->tempoInicial;

            break;

        default:
            break;

    }

    // Printagem do resultado da operacao
    InfoOrdenacao->diferenca = (double)(InfoOrdenacao->diferenca*1000)/(double)CLOCKS_PER_SEC;
    printf("\n Comparacoes (Vetor Ordenado Inversamente): %d \n Trocas (Vetor Ordenado Inversamente): %d", InfoOrdenacao->comparacoes, InfoOrdenacao->trocas);
    printf("\n Tempo (Vetor Ordenado Inversamente): %lf ms\n", InfoOrdenacao->diferenca);

    free(vetor);
}








// ############################## MAIN ################################

int main()
{
    // Deixando todas as chamadas da funcao rand() com a semente do tempo local
    srand((unsigned)time(NULL)); 

    // Criando variavel que armazena todas as estatisiticas das ordenações
    TInfo *InfoBubble = criarInfo();
    TInfo *InfoQuick = criarInfo();
    TInfo *InfoHeap = criarInfo();
    TInfo *InfoMerge = criarInfo();


    // Operacoes
    fazerMedia(BUBBLESORT, InfoBubble);
    comVetorOrdenado(BUBBLESORT, InfoBubble);
    comVetorOrdenadoInversamente(BUBBLESORT, InfoBubble);

    fazerMedia(QUICKSORT, InfoQuick);
    comVetorOrdenado(QUICKSORT, InfoQuick);
    comVetorOrdenadoInversamente(QUICKSORT, InfoQuick);

    fazerMedia(HEAPSORT, InfoHeap);
    comVetorOrdenado(HEAPSORT, InfoHeap);
    comVetorOrdenadoInversamente(HEAPSORT, InfoHeap);

    fazerMedia(MERGESORT, InfoMerge);
    comVetorOrdenado(MERGESORT, InfoMerge);
    comVetorOrdenadoInversamente(MERGESORT, InfoMerge);


    // Liberando Memoria
    free(InfoBubble);
    free(InfoQuick);
    free(InfoHeap);
    free(InfoMerge);



    //  deixando o executavel aberto
    printf("\n\n Digite Ctrl+C para finalizar: ");
    for(;;);

    

    return 0;

}



