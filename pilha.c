#include "stdio.h"
#include "stdlib.h"
#include "lse.h"
#include "pilha.h"

struct pilha{
	int alt;//altura fds
	TLista *dados;//listas caraio
};

TPilha *criarPilha(){
	TPilha *p = malloc(sizeof(TPilha));
	p->alt = 0;
	p->dados = criarLSE();

	return p;
}

void empilhar(TPilha *pilha, void *dado){
	inserirLSE(pilha->dados, dado);
	pilha->alt++;
}

typedef void (*TDestroyPilha)(void*);
void desempilhar(TPilha *pilha, TDestroyPilha destroy){
	if(pilha->alt > 0){
		removerLSE(pilha->dados,destroy);
		pilha->alt--;
	}
	else{
		printf("Pilha vazia\n");
	}
}

int alturaPilha(TPilha *pilha){
	return pilha->alt;
}

void *topoPilha(TPilha *pilha){
	void *topo = acessarLSE(pilha->dados, 1);
	return topo;
}