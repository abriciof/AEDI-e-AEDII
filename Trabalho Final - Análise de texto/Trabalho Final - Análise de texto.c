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
#include <string.h>
#include <ctype.h>



// ######################## ESTRUTURAS ##############################


// > LISTA ENCADEADA

// Estrutura do Tipo Elemento de Lista
typedef struct e TELE;
struct e{
	char *palavra;
	TELE *prox;
};

// Estrutura do Tipo Lista Encadeada
typedef struct lista TLista;
struct lista{
	TELE *inicio;
	TELE *fim;
    int qtde_palavras;
};


// > ÁRVORE AVL

// AVL de inteiros
typedef struct NO TNO;

struct NO{
    int info, alt; // Número da categoria
    TLista *todas_palavras; // Guardar as palavras
    TNO *esq, *dir; // Filhos esquerdo e direito
}; 






// ######################## DECLARAÇÕES ##############################


// > LISTA ENCADEADA
TLista *criarLista();
void inserirListaOrdem(TLista* lista, char *palavra);
void imprimirLista(TLista *lista);
void mostrar10primeiros(TLista *lista);
TELE *busca(TELE *ele, char *buscado);

// > ÁRVORE AVL
TNO *criarNO(int info);
TNO *criarAVL();
int altura(TNO *raiz);
TNO *RotDireita(TNO *p);
TNO *RotEsquerda(TNO *p);
TNO *RotEsquerdaDireita(TNO *raiz);
TNO *RotDireitaEsquerda(TNO *raiz);
int FB(TNO *raiz);
TNO *inserir(TNO *raiz, int info);
TNO *buscaBinaria(TNO *raiz, int chave);
void printar(TNO *raiz);
int soma(TNO *raiz);






// ####################### FUNÇÕES LISTA #############################


// Criação de uma lista para que se possa trabalhar as linhas das palavras
// Como nao sabemos quantas palavras aparecem em n linhas, então uma lista
// encadeada é um boa e simples solução
TLista *criarLista(){
    TLista *aux = malloc(sizeof(TLista));
    aux->inicio = NULL;
    aux->fim = NULL;
    aux->qtde_palavras = 0; // contador de palavras de cada lista
    return aux;
}

// Inserir Ordenado na lista de Strings
void inserirListaOrdem(TLista* lista, char *palavra){

	TELE *p = lista->inicio;
	TELE *anterior = NULL;

    // Novo elemento
    TELE *novo = malloc(sizeof(TELE));
    novo->palavra = malloc(sizeof(char)*40);
    strcpy(novo->palavra, palavra);
	novo->prox = NULL;

    // Lista Vazia
    if(p == NULL){
		lista->inicio = novo;
        lista->qtde_palavras++;
        return;
	}
    
    // Apenas um elemento
    if(p->prox == NULL){
        if(strcmp(p->palavra, palavra) < 0){
            p->prox = novo;
        }else{
            lista->inicio = novo;
            novo->prox = p;
        }
        lista->qtde_palavras++;
        return;
	}

    // Se a entrada for menor que o primeiro
    // Inserindo no começo
    if(strcmp(p->palavra, palavra) > 0){
        lista->inicio = novo;
        novo->prox = p;
        lista->qtde_palavras++;
        return;
    }

	// Procurando posição para inserção
	while((p != NULL) &&  (strcmp(p->palavra, palavra)<0)){
		anterior = p;
		p = p->prox;
	}

	// Inserindo entre dois elementos
    // Inserindo no final
    anterior->prox = novo;
    novo->prox = p;
    lista->qtde_palavras++;
	return;
}

// Mostra os elementos char* que foram inseridos anteriormente
// na lista encadeada
// Função não é utilizada na solução, apenas para fins de estudo
void imprimirLista(TLista *lista){
    TELE *aux = lista->inicio;
    while(aux!=NULL){
        printf(" %s", aux->palavra);
        aux = aux->prox;
    }
}

// Apenas mostras as 10 primeiras strings
// Lista já está ordenada
void mostrar10primeiros(TLista *lista){
    TELE *aux = lista->inicio;
    for(int i=0; i<10; i++){
        if(aux!=NULL){
            printf("\n%s", aux->palavra);
            aux = aux->prox;
        }else{
            break;
        }
        
    }
}

// Faz a busca de um elemento na lista
// Caso esteja presente, é retornado
// Caso contrário, NULL
// Tudo isso, recursivamente
TELE *busca(TELE *ele, char *buscado){
    if(ele != NULL){
        if(strcmp(ele->palavra, buscado)==0)
        return ele;
    
        if(ele->prox!=NULL)
        return busca(ele->prox, buscado);
    }
    return NULL;
}






// #################### FUNÇÕES ÁRVORE AVL #########################


// Criando Nó da Árvore
TNO *criarNO(int info){
    TNO *no = malloc(sizeof(TNO));
    no->info = info;
    no->alt = 0;
    no->esq = NULL;
    no->dir = NULL;
    no->todas_palavras = criarLista();
    return no;
}

// Criando uma Árvore AVL
TNO *criarAVL(){
    TNO *raiz = malloc(sizeof(TNO));
    if(raiz!=NULL) raiz = NULL;
    return raiz;
}

// Altura de cada Nó, para cálculo do balanceamento
int altura(TNO *raiz){
    int altura_esquerda, altura_direita;
    if(raiz == NULL) return 0;

    if(raiz->esq == NULL) altura_esquerda = 0; 
    else altura_esquerda = 1 + raiz->esq->alt; 

    if(raiz->dir == NULL) altura_direita = 0; 
    else altura_direita = 1 + raiz->dir->alt; 

    if(altura_esquerda > altura_direita) return altura_esquerda; 

    return altura_direita;
}

//Rotação à Direita da AVL
TNO *RotDireita(TNO *p){
    TNO *aux = p->esq;
    p->esq = aux->dir;
    aux->dir = p;
    p->alt = altura(p);
    aux->alt = altura(aux);
    return aux;
}
 
// Rotação à Esquerda da AVL
TNO *RotEsquerda(TNO *p){
    TNO *aux = p->dir;
    p->dir = aux->esq;
    aux->esq = p;
    p->alt = altura(p);
    aux->alt = altura(aux);
    return aux;
}
  
// Rotação Esquerda-Direita da AVL
TNO *RotEsquerdaDireita(TNO *raiz){
    raiz->esq = RotEsquerda(raiz->esq);
    raiz = RotDireita(raiz);
    return raiz;
}
 
// Rotação Direita-Esquerda da AVL
TNO *RotDireitaEsquerda(TNO *raiz){
    raiz->dir = RotDireita(raiz->dir);
    raiz = RotEsquerda(raiz);
    return raiz;
}

// Cálculo do Fator de Balanceamento
int FB(TNO *raiz){ 
    int altura_esquerda, altura_direita;
    if(raiz == NULL) return 0; 

    if(raiz->esq == NULL) altura_esquerda = 0; 
    else altura_esquerda = 1 + raiz-> esq->alt; 

    if(raiz->dir == NULL) altura_direita = 0; 
    else altura_direita = 1 + raiz->dir->alt; 

    return(altura_esquerda - altura_direita);
}

// Inserção na Árvore e Balanceamento da mesma, recursivamente
TNO *inserir(TNO *raiz, int info){
    if(raiz == NULL) raiz = criarNO(info); 
    else{
        if(info > raiz->info){
            raiz->dir = inserir(raiz->dir, info);
            if(FB(raiz) == -2){
                if(info > raiz->dir->info) raiz = RotEsquerda(raiz); 
                else raiz = RotDireitaEsquerda(raiz); 
            }
        }
        else{
            if(info < raiz->info){
                raiz->esq = inserir(raiz->esq, info);
                if(FB(raiz) == 2){
                    if(info < raiz->esq->info) raiz = RotDireita(raiz); 
                    else raiz = RotEsquerdaDireita(raiz); 
                }
            }
        }
    }
    raiz->alt = altura(raiz);
    return raiz;
}

//  Faz uma busca binária na Árvore, recursivamente
TNO *buscaBinaria(TNO *raiz, int chave){
	if (raiz == NULL) return NULL;
	if (raiz->info == chave) return raiz;
	if (raiz->info < chave) 
		return buscaBinaria(raiz->dir, chave);

	return buscaBinaria(raiz->esq, chave);
}

// Imprimir a AVL em Ordem, recursivamente
// Função não é utilizada na solução, apenas para fins de estudo
void printar(TNO *raiz){
    if(raiz != NULL){
        printar(raiz->esq);
        printf("%d ", raiz->info);
        printar(raiz->dir);
    }
}

// Faz o somatório de todas as palavras da Árvore AVL, recursivamente
int soma(TNO *raiz){
    if(raiz != NULL){
        TLista *listona = raiz->todas_palavras;
        return (listona->qtde_palavras + soma(raiz->esq) + soma(raiz->dir));
    }else{
        return 0;
    }
}





// ############################ MAIN ################################

int main(int argc, char** argv){

    // Vamos chamar algum arquivo txt como entrada do programa
    // Se o arquivo for aberto o programa funciona normalmente
    // Caso contrário, é exibido um mensagem e o programa é encerrado
    FILE *file;
    if((file = fopen(argv[1], "r"))==NULL){
        printf ("\n Erro na abertura do arquivo.");
        return 0;
    }
    
    // Declarando a raiz da Árvore AVL
    TNO *raiz = criarAVL();


    char *palavra = malloc(sizeof(char)*41); // 40 caracteres + 1
    TNO *buscado = NULL;
    TLista *listona = NULL;
    int categoria;


    // Guarda o total de frases no documento
    int qtde_frases_totais = 0;

    // Vetor que vai guardar qual o maior número de frases
    // o índice do vetor vai dizer qual é a categoria
    // já que temos categorias de [0, 1000[
    int categorias_frases[1000];

    // Inicializando o vetor com zeros
    for(int i=0; i<1000; i++)
        categorias_frases[i] = 0;


    // Enquanto não chegar no fim do documento, execute...
    while(!feof(file)){

        // Escaneando a primeira palavra, que é um número    
        fscanf(file, "%s", palavra);

        // Temos que transformar a string em número inteiro
        categoria = atoi(palavra);

        // Incrementando a quantidade de frases totais
        // Utilizada para fins de verificação
        // Não mostrada na saída de dados
        qtde_frases_totais++;

        // Incrementando o vetor de quantidade de frases
        // Tendo como índice a categoria
        categorias_frases[categoria]++;


        // Verificando se a Árvore já tem um nó com a chave categoria
        if(buscaBinaria(raiz, categoria) == NULL){ 
            // Caso não esteja na árvore, é inserido na AVL
            // e se preciso, é feito o balanceamento da árvore
            raiz = inserir(raiz, categoria);  
        }

        // De qualquer forma vai encontrar a categoria, seja inserida antes ou agora
        buscado = buscaBinaria(raiz, categoria); 

        // Como buscado não é NULL, podemos obter a lista da estrutura
        listona = buscado->todas_palavras;

        // Escaneando a próxima palavra do documento
        fscanf(file, "%s", palavra); 

        // Enquanto a palavra lida não for um "." (ponto final)
        while(strcmp(palavra, ".")!=0){

            // Não aceitando palavras menores que 4
            if(strlen(palavra)>3){
                
                // Transformando a string para minúscula
                palavra = strlwr(palavra); 

                // Caso a palavra já esteja na lista
                if(busca(listona->inicio, palavra) == NULL){ 
                    // Insere e conta a palavra, tudo dentro da função
                    inserirListaOrdem(listona, palavra);
                }else{
                    // Caso contrário, apenas aumenta +1 no contador
                    listona->qtde_palavras++;
                }
            }
            // Escaneando a próxima palavra
            fscanf(file, "%s ", palavra);
        }
    }


    // Fechando o arquivo aberto anteriormente
    fclose(file);

    // Vetor maior, guarda o maior número de frases no índice [0]
    // e guarda a categoria do maior número de frases no índide [1]
    int maior[2] = {0, -1};

    // Verficando o maior número de frases
    for(int i=0; i<1000; i++)
        if(categorias_frases[i] > maior[0]){
            maior[0] = categorias_frases[i];
            maior[1] = i;
        }
            

    // Verificando e imprimindo a soma de palavras da Árvore como um todo
    // Verificando e imprimindo a categoria com maior número de frases
    int somatorio_palavras = soma(raiz);
    printf("Palavras totais: %d\nMaior categoria: %d\n", somatorio_palavras, maior[1]);
    //printf("\nFrases: %05d\n", qtde_frases);
        

    // Após a printagem dos resultados pedidos, vamos busca por categorias e mostrar na
    // tela as 10 primeiras palavras em ordem alfabética


    int entrada;
    TNO *auxiliar = NULL;


    // Faça ... Enquanto a entrada for diferente de -1
    do{
        scanf("%d", &entrada);
        auxiliar = buscaBinaria(raiz, entrada);
        if(auxiliar != NULL){ // Caso a entrada esteja presente na árvore
            printf("\n\nCategoria %d", entrada);
            mostrar10primeiros(auxiliar->todas_palavras);
        }
    }while(entrada!=-1);



    

    return 0;
}













