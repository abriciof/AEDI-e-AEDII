#include "stdio.h"
#include "stdlib.h"
#include "lse.h"

TELE *criarELE(void *cargautil){
		TELE *e = malloc(sizeof(TELE));
		e->cargautil = cargautil;
		e->prox = NULL;

		return e;
}


TLista *criarLSE(){
	TLista *lse = malloc(sizeof(TLista));

	lse->inicio = NULL;
	lse->fim = NULL;
	lse->qtde = 0;

	return lse;
}


void inserirLSE(TLista *lse, void *novo){

	TELE *ele = criarELE(novo);

	if (lse->inicio == NULL){
		lse->inicio = ele;
		lse->fim = ele;
	}else{
		ele->prox = lse->inicio;
		lse->inicio = ele;
	}
	lse->qtde++;
}

void inserirFimLSE(TLista *lse, void *novo){

	TELE *ele = criarELE(novo);

	if(lse->inicio == NULL){
		lse->inicio = ele;
		lse->fim=ele;
	}else{
		TELE* ultimo = lse->fim;

		ultimo->prox = ele;
		lse->fim= ele;
	}
	lse->qtde++;
}

void removerLSE(TLista* lse, TDestroyLSE destroy){
	TELE* primeiro = lse->inicio;
	printf("---removendo---\n");
	if (primeiro != NULL){
		void *cargautil=primeiro->cargautil;
		// unico elemento?
		if(lse->inicio == lse->fim){
			lse->inicio=NULL;
			lse->fim=NULL;
		}else{// caso geral
			lse->inicio = primeiro->prox;
		}
		//liberou a memoria
		free(primeiro);
		destroy(cargautil);
		lse->qtde--;
	}

}

void imprimirLSE(TLista *lse, TImpressoraLSE imprimir)
{
	TELE *cam = lse->inicio;
	while(cam!=NULL){
	  imprimir(cam->cargautil);
		//printf("%p %p %p\n", cam, cam->cargautil, cam->prox);
		cam=cam->prox;
	}

}

void removerFinalLSE(TLista *lse, TDestroyLSE destroy){
	TELE *cam=lse->inicio;
	if (lse->inicio==NULL){ // lista vazia
		printf("Lista vazia\n");
	}else if (lse->inicio == lse->fim){ // unico
		lse->inicio = NULL;
		lse->fim = NULL;
		lse->qtde = 0;

		destroy(cam->cargautil);
		free(cam);
	}else{ // pelo menos dois elementos na lista
		while(cam->prox!=lse->fim){
			cam = cam->prox;
		}
		destroy(lse->fim->cargautil);
		free(lse->fim);
		lse->fim=cam;
		cam->prox=NULL;
		lse->qtde--;
	}
}

void removerPosicaoLSE(TLista *lse, int pos, TDestroyLSE destroy){
	if (pos == 1){
		removerLSE(lse, destroy);
	}else if(pos == lse->qtde){
		removerFinalLSE(lse,destroy);
	}else{
		TELE *cam = lse->inicio;
		TELE *anterior = NULL;
		int contador = 1;
		while(pos > contador){
			anterior = cam;
			cam = cam->prox;
			contador++;
		}
		anterior->prox = cam->prox;
		destroy(cam->cargautil);
		free(cam);
		lse->qtde--;
	}
}

void *acessarLSE(TLista *lse, int pos){
	TELE *cam = NULL;
	void *cargautil = NULL;
	if ( (pos>0) && (pos<=lse->qtde) ){
		cam = lse->inicio;
		int contador = 1;
		while(contador<pos){
			cam = cam->prox;
			contador++;
		}
		cargautil = cam->cargautil;
	}

	return cargautil;
}

void *buscarLSE(TLista *lse, void* buscado, TCompararLSE comparar){
	TELE *cam = NULL;

	cam = lse->inicio;
	while( (cam!=NULL) && comparar(buscado,cam->cargautil)!=0){
		cam = cam->prox;
	}
	if(cam == NULL){
		return NULL;
	}else{
		return cam->cargautil;
	}
}

void removerConteudoLSE(TLista *lse, int long chave, TCompararConteudoLSE comparar){
	TELE *cam = lse->inicio;
	TELE *anterior = NULL;
	while ( (cam!=NULL) && comparar(chave, cam->cargautil) != 0 ){
		anterior = cam;
		cam = cam->prox;
	}
	if (cam==NULL){
		printf("404 - Not Found\n");
	}else{
		if(lse->inicio == lse->fim){
			lse->fim=NULL;
			lse->inicio=NULL;
		}else if (cam == lse->inicio){
			lse->inicio = cam->prox;
		}else if(cam == lse->fim){
			lse->fim = anterior;
			anterior->prox = NULL;
		}else{
			anterior->prox = cam->prox;
		}
		free(cam);
		lse->qtde--;
	}
}

