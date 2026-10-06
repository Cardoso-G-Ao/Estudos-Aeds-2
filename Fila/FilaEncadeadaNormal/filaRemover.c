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
void remover(Celula **primeiro , Celula **ultimo){
    if((*primeiro)==(*ultimo)){
        printf("erro");
        return;
    }
    Celula *tmp = (*primeiro);
    (*primeiro) = (*primeiro)->prox;
    int elemento = (*primeiro)->elemento;
   tmp->prox = NULL;
   free(tmp);
   tmp =NULL;
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


    remover(&primeiro,&ultimo);


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