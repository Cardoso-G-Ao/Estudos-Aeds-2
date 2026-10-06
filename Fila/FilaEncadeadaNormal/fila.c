#include <stdio.h>
#include <stdlib.h>

typedef struct Celula
{
    int elemento;
    struct Celula *prox;
} Celula;

Celula *novaCelula(int elemento)
{
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->elemento = elemento;
    nova->prox = NULL;
    return nova;
}
void inserir(Celula **primeiro , Celula **ultimo){
    int x;
    scanf("%d",&x);
    (*ultimo)->prox = novaCelula(x);
    (*ultimo) = (*ultimo)->prox;
}


int main(){
    int valor;
    Celula *primeiro = NULL;
    Celula *ultimo = NULL;
    while(scanf("%d",&valor) == 1){
    Celula *nova = novaCelula(valor);

        if(primeiro == NULL){
            primeiro = nova;
            ultimo = nova;
        }else {
            ultimo->prox = nova;
            ultimo = nova;
        }

    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);


    inserir(&primeiro,&ultimo);

for();
    Celula *atual = primeiro;
    while (atual != NULL) {
        printf("%d ", atual->elemento);
        atual = atual->prox; 
    }
    printf("\n");

    atual = primeiro;
    while (atual != NULL) {
        Celula *proxima = atual->prox; 
        free(atual);                   
        atual = proxima;               
    }

    return 0;
}