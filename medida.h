typedef struct Medida TMedida;

TMedida *criarMedida(int chave, int tempo, double temp, double lat, double lgt, double presao, double densidade);
void imprimirMedida(void *medida);
int compararMedida(void *buscado, void *medida);
int compararConteudoMedida(int long chave, void *medida);
void destroyMedida(void *medida);