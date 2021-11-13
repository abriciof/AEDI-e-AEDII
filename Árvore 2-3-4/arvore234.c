/*--------------------------------------------------

  UFAM - UNIVERSIDADE FEDERAL DO AMAZONAS

ALUNO: FABRÍCIO DA COSTA GUIMARÃES
MATRICULA: 21950515
DISCIPLINA: ALGORITMOS E ESTRUTURAS DE DADOS II
PERIODO: ESPECIAL ERE/2020
PROFESSOR: EDSON NASCIMENTO

----------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 400



// ######################## ESTRUTURAS ##############################

typedef struct no TNO;
typedef struct no{
  TNO *pai;
  TNO *filhos[4];
  int chave[3];
  int qtde;
}no;



// ######################## PROTÓTIPOS ##############################

void inserir(TNO*,int);
void remover(TNO*, int);
int procura(TNO*, int);
void insere(TNO*, int);
void dividir(TNO *, TNO *);
int existe(TNO*, int);
int raiz(TNO*);
int folha(TNO*);
TNO *achaFilho(TNO*, int);
void insereValor(TNO*, int);
void imprimir(TNO*);
void ordena(TNO*);
TNO *sucessor(TNO*, int);
int rotacao(TNO*);
void remova(TNO*, int);
TNO *busca(TNO*, int);



// ################### FUNÇÕES ÁRVORE 2-3-4 ##########################

// Cria uma arvore 2-3-4
TNO *criaArv(){
  TNO *raiz = malloc(sizeof(TNO));
	for(int i=0;i<4;i++) raiz->filhos[i] = NULL;
  for(int i=0; i<3; i++) raiz->chave[i] = 0;
	raiz->qtde = 0;
	raiz->pai = NULL;
  return raiz;
}

// Verifica se nó é raiz
int raiz(TNO *no){
  if(no->pai == NULL) return 1;
  else return 0;
}

// Verifica se nó é folha
int folha(TNO* atual){
  if(atual->filhos[0] == NULL) return 1; 
  else return 0;
}

// Verifica de valor está no nó
int existe(TNO *no, int elemento){
  int tam = no->qtde;
  for(int i = 0; i<=tam-1; i++)
    if(no->chave[i] == elemento)
      return 1;

  return 0;
}

// Encontra o filho do nó onde está o valor
TNO *achaFilho(TNO *no, int elemento){
  int tam = no->qtde;
  if(folha(no)) return 0;
  else{     //se nao for folha, busca posicao do filho
    for(int i=0;i<=tam-1;i++)
      if(no->chave[i] > elemento)   //se a chave for maior que o valor
        return no->filhos[i];       //troca: filho vai pra posicao
      
    //se o valor for maior que todos os elementos, ultimo filho
    return no->filhos[tam];
  }
}

// Busca o valor na Árvore 2-3-4 e retorna
TNO *busca(TNO *raiz, int elemento){
  TNO *atual = raiz;
  //percorrer para achar uma folha
  while(atual!=NULL){
    if(existe(atual, elemento))  //verificar se valor esta no no
      return atual;
    else
      atual = achaFilho(atual, elemento);  //busca o prox
  }
  return 0;
}


// Retorno da Busca 0 ou 1
int procura(TNO *raiz, int elemento){
  if(busca(raiz, elemento) != NULL) return 1;
  else return 0;
}


// Insere na Árvore 2-3-4
void inserir(TNO *raiz, int elemento){
  TNO *atual = raiz;
  while(1){
    if(atual->qtde == 3){
      dividir(raiz, atual);
      atual = atual->pai;
      atual = achaFilho(atual, elemento);
    }
    else if(folha(atual)) break;
    else atual = achaFilho(atual, elemento);
  }
  insereValor(atual, elemento);
}

// Divide um nó cheio (4 elementos)
void dividir(TNO *Arv234, TNO *no){
  //tipoNo *raiz;
  if(raiz(no)){
    TNO *temp = malloc(sizeof(TNO));
    for(int i=0;i<4;i++) temp->filhos[i]=NULL;
    temp->filhos[1] = no;
    temp->pai = NULL;
    temp->qtde = 1;
    temp->chave[0] = no->chave[1];

    TNO *aux = malloc(sizeof(TNO));
    for(int i = 0;i<4;i++) aux->filhos[i] = NULL;
    for(int i=0; i<3; i++) aux->chave[i] = 0;
    aux->filhos[1] = no;
    aux->pai = temp;
    aux->qtde = 1;
    aux->chave[0] = no->chave[2];
    if(!folha(no)){
      aux->filhos[0] = no->filhos[2];
      (no->filhos[2])->pai = aux;
      aux->filhos[1] = no->filhos[3];
      (no->filhos[3])->pai = aux;
    }

    temp->filhos[0]= no;
    temp->filhos[1]= aux;
    no->pai = temp;
    no->qtde = 1;
    Arv234 = temp;

  }else{
    TNO *paiNo = no->pai;
    paiNo->chave[paiNo->qtde++]= no->chave[1];

    TNO *aux = malloc(sizeof(TNO));
    for(int i=0; i<3;i++) aux->filhos[i] = NULL;
    for(int i=0; i<3; i++) aux->chave[i] = 0;
    aux->filhos[1] = no;
    aux->pai = paiNo;
    aux->qtde = 1;
    aux->chave[0] = no->chave[2];
    if(!folha(no)){
      aux->filhos[0] = no->filhos[2];
      (no->filhos[2])->pai = aux;
      aux->filhos[1] = no->filhos[3];
      (no->filhos[3])->pai = aux;
    }

    paiNo->filhos[paiNo->qtde] = aux;
    no->qtde = 1;
  }
    ordena(no->pai);
}

// Insere o valor a um nó
void insereValor(TNO *no, int elemento){
  int tam = no->qtde;
  no->chave[tam] = elemento;
  no->qtde++;
  ordena(no);
}

// Ordena o pai
void ordena(TNO *no){
  int tam = no->qtde;
  int aux;
  for(int i=0; i<tam; i++)
    for(int j=i+1; j<tam; j++)
      if(no->chave[i] > no->chave[j]){
        aux = no->chave[i];
        no->chave[i]= no->chave[j];
        no->chave[j]=aux;
      }
    
  if(!folha(no)){
    TNO *aux;
    for(int i=0; i<=tam; i++)
			for(int j=i+1; j<=tam; j++)
				if((no->filhos[i])->chave[0] > (no->filhos[j])->chave[0]){
					aux = no->filhos[i];
					no->filhos[i] = no->filhos[j];
					no->filhos[j] = aux;
				}
  }
}

// Nó sucessor
TNO *sucessor(TNO *no, int elemento){
  if(!folha(no))
    for(int i = 0; i < no->qtde; i++)
      if (no->chave[i] == elemento) {
        no = no->filhos[i+1];
        break;
      }
  
  while(!folha(no)){
    no = no->filhos[0];
  }
  return no;
}

// Remove a chave de um nó
void remova(TNO *no, int elemento){
  int posicao;
  for(int i=0; i < no->qtde; i++){
    if(no->chave[i] == elemento){
      posicao = i;
    }
  }
  for(int j = posicao; j < no->qtde-1; j++)
    no->chave[j] = no->chave[j+1];
  
  no->qtde--;
}

// Rotaciona nós
int rotacao(TNO *no){
  int posicao;
  TNO *paiNo = no->pai;
  TNO *irmao;
  if(!raiz(no)){
    for(int i = 0; i <= paiNo->qtde; i++)
      if(paiNo->filhos[i] == no){
        posicao = i;
        break;
      }
    
    int tamIrmao;
    if(posicao>0){
      irmao = paiNo->filhos[posicao-1];
      tamIrmao = irmao->qtde;
      if(irmao->qtde > 1){
        insereValor(no, paiNo->chave[posicao-1]);
        paiNo->chave[posicao-1] = irmao->chave[tamIrmao-1];
        remova(irmao, irmao->chave[tamIrmao-1]);
        return 1;
      }
    }

    if(posicao<paiNo->qtde){
      irmao = paiNo->filhos[posicao+1];
      if(irmao->qtde>1){
        insereValor(no, paiNo->chave[posicao]);
        paiNo->chave[posicao] = irmao->chave[0];
        remova(irmao, irmao->chave[0]);
        return 1;
      }
    }
  }
  return 0;
}

// Remove um nó da Árvore
void remover(TNO* raiz, int elemento){
  TNO *atual = busca(raiz, elemento);
  TNO *aux;
  int trocado;

  if(atual!=NULL){
    if(!folha(atual)){
      for(int i=0; i<atual->qtde; i++)
        if(atual->chave[i] == elemento){
          aux = sucessor(atual,elemento);
          atual->chave[i] = aux->chave[0];
          trocado = atual->chave[i];
          break;
        }
    
      atual = aux;
      remova(atual,trocado);
    }
    else remova(atual,elemento);
    
  }
  while(1){
    if(atual->qtde != 0){
      return ;
    }else if(rotacao(atual)){
      return;
    }else{
      TNO *paiNo  = atual->pai;
      if (paiNo->qtde == 1){
        if(paiNo->filhos[0] != atual)
          insereValor(paiNo, (paiNo->filhos[0])->chave[0]);
        if(paiNo->filhos[1] != atual)
          insereValor(paiNo, (paiNo->filhos[1])->chave[0]);
        
        atual = paiNo;
        atual->filhos[0] = 0;
        return;
      }else{
        int posicao;
        TNO *irmao;
        for(int i=0; i <= paiNo->qtde; i++){
          if(paiNo->filhos[i] == atual){
            posicao = i;
            break;
          }
        }
        if(posicao < paiNo->qtde){
          irmao = paiNo->filhos[posicao+1];
          insereValor(atual, paiNo->chave[posicao]);
          insereValor(atual, irmao->chave[0]);
          remova(paiNo, paiNo->chave[posicao]);
          for(int i = posicao+1; i<paiNo->qtde+1; i++){
            paiNo->filhos[i] = paiNo->filhos[i+1];
          }
          return;
        }else{
          irmao = paiNo->filhos[posicao-1];
          insereValor(atual, paiNo->chave[posicao-1]);
          insereValor(atual, irmao->chave[0]);
          paiNo->filhos[posicao-1] = atual;
          remova(paiNo, paiNo->chave[posicao-1]);
          return;
        }
      }
    }
  }
}

// Imprime a Árvore
void printar(TNO *no, int nivel) {
  if (no == NULL) return;
  else {
    for (int i = 0; i < no->qtde; i++) 
      printf("%d %d %d\n", nivel, i, no->chave[i]);
    
    for (int i = 0; i < no->qtde+1; i++) {
      nivel++;
      printar(no->filhos[i], nivel);
      nivel--;
    }
  }
}




// ############################ MAIN ################################


int main(){

  srand((unsigned)time(NULL));

	// Criando Árvore 2-3-4
  TNO *Arv234 = criaArv();
	int entrada;

	// Inserindo 300 chaves aleatórios
  for(int i=0; i<300; i++){
		entrada = rand()%MAX;
		if(!procura(Arv234, entrada))
			inserir(Arv234, entrada);
	}

	// Mostrando a Árvore( Nivel, Indice e Chave)
	// A partir do Nível 0
	printar(Arv234, 0);

	// Gerando chaves random e verificando se está na Árvore 2-3-4
	for(int i=0; i<80; i++){

		entrada = rand()%MAX;

		if(procura(Arv234, entrada)){ // Caso a chave esteja na Árvore
			TNO *buscado = busca(Arv234, entrada);
			printf("\n Chave %02d estava no nivel %d e na posiçao %d", entrada, (buscado->pai)->qtde, buscado->qtde);
			remover(Arv234, entrada);
			free(buscado);
		}
		
		else	// Caso contrário
			printf("\n o valor %03d não encontra-se na arvore", entrada);
		
	}


	// Deixando o executável aberto
	printf("\n\n Digite Ctrl+C para finalizar: ");
	for(;;);

  return 0;
}


