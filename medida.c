#include "stdio.h"
#include "stdlib.h"
#include "medida.h"

// #include "lse.h"

struct Medida
{
	int long chave;
	int tempo;
	double temp;
	double lat, lgt;
	double presao;
	double densidade;
};


TMedida *criarMedida(int chave, int tempo, double temp, double lat, double lgt, double presao, double densidade){
	TMedida *medida = malloc(sizeof(TMedida));

	medida->chave = chave;
	medida->tempo = tempo;
	medida->temp = temp;
	medida->lat = lat;
	medida->lgt = lgt;
	medida->presao = presao;
	medida->densidade = densidade;
	return medida;
}

void imprimirMedida(void *medida){
	TMedida *m = medida;
	if (m!=NULL){
		printf("%ld %d %lf %lf %lf %lf %lf\n",m->chave, m->tempo, m->temp, m->lat, m->lgt, m->presao, m->densidade );
	}else{
		printf("Medida Indefinida\n");
	}
}

int compararMedida(void *buscado, void *medida){
	TMedida *m = medida;
	TMedida *b = buscado;
	int resultado;

	if(b->tempo == m->tempo){
		resultado = 0;
	}else if(b->tempo > m->tempo){
		resultado = 1;
	}else{
		resultado = -1;
	}

	printf("---Comparando medida: retornando:%d ----\n",resultado);
	return resultado;
}

int compararConteudoMedida(int long chave, void *medida){
	TMedida *m = medida;
	int resultado;

	if(chave == m->chave){
		resultado = 0;
	}else if(chave > m->chave){
		resultado = 1;
	}else{
		resultado = -1;
	}

	printf("---Comparando medida: retornando:%d ----\n",resultado);
	return resultado;
}

void destroyMedida(void *medida){
	TMedida *m = medida;
	printf("----Destroy medida ----\n");
	free(m);
}

// int main(int argc, char const *argv[])
// {
// 	int tempo;
// 	double temperatura;
// 	double lat, lgt, presao, densidade;

// 	TLista* lst = criarLSE();
// 	int long chave=1;

// 	scanf("%d",&tempo);
// 	while(tempo>=0){
// 		scanf("%lf%lf%lf%lf%lf",&temperatura, &lat, &lgt, &presao, &densidade);

// 		TMedida* m = criarMedida(chave, tempo, temperatura, lat, lgt, presao, densidade);
// 		inserirFimLSE(lst, m);

// 		chave = chave + 1;

// 		scanf("%d", &tempo);
		
// 	}
	
// 	imprimirLSE(lst, imprimirMedida);

// 	removerConteudoLSE(lst, 3, compararConteudoMedida);
	
// 	removerPosicaoLSE(lst,1,destroyMedida);

// 	imprimirLSE(lst, imprimirMedida);

// 	return 0;
// }
