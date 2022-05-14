#include "stdio.h"
#include "medida.h"
#include "pilha.h"

int main(){
	int tempo;
	double temperatura;
	double lat, lgt, presao, densidade;

	TPilha* pilha = criarPilha();
	int long chave=1;

	scanf("%d",&tempo);
	while(tempo>=0){
		scanf("%lf%lf%lf%lf%lf",&temperatura, &lat, &lgt, &presao, &densidade);

		TMedida* m = criarMedida(chave, tempo, temperatura, lat, lgt, presao, densidade);
		empilhar(pilha, m);

		chave = chave + 1;

		scanf("%d", &tempo);
		
	}
	TMedida *m = topoPilha(pilha);
	imprimirMedida(m);
	desempilhar(pilha, destroyMedida);
	int altura = alturaPilha(pilha);
	printf("altura: %d\n", altura);
	return 0;
}
