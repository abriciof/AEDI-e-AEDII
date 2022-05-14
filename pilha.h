typedef struct pilha TPilha;
typedef void (*TDestroyPilha)(void*);

TPilha *criarPilha();
void empilhar(TPilha *pilha, void *dado);
void desempilhar(TPilha *pilha, TDestroyPilha destroy);
int alturaPilha(TPilha *pilha);
void *topoPilha(TPilha *pilha);
