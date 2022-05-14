typedef struct ele TELE;
struct ele{
	void *cargautil;
	TELE *prox;
};

typedef struct lista TLista;
struct lista{
	int qtde;
	TELE *inicio;
	TELE *fim;
};

typedef void (*TDestroyLSE)(void*);
typedef void (*TImpressoraLSE)(void*);
typedef int (*TCompararLSE)(void*,void*);
typedef int (*TCompararConteudoLSE)(int long,void*);

TLista *criarLSE();
void inserirLSE(TLista *lse, void *novo);
void inserirFimLSE(TLista *lse, void *novo);
void removerLSE(TLista* lse, TDestroyLSE destroy);
void imprimirLSE(TLista *lse, TImpressoraLSE imprimir);
void removerFinalLSE(TLista *lse, TDestroyLSE destroy);
void removerPosicaoLSE(TLista *lse, int pos, TDestroyLSE destroy);
void *acessarLSE(TLista *lse, int pos);
void *buscarLSE(TLista *lse, void* buscado, TCompararLSE comparar);
void removerConteudoLSE(TLista *lse, int long chave, TCompararConteudoLSE comparar);



