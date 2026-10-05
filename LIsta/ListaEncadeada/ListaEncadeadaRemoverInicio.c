#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
    int elemento;
    struct Celula *prox;
}Celula;

Celula *novaCelula(int elemento)
{
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->elemento = elemento;
    nova->prox = NULL;
    return nova;
}
void removerInicio(Celula **ultimo,Celula **primeiro){
    if((*ultimo)==(*primeiro)){
        printf("erro");
        return;
    }
    Celula *tmp = (*primeiro)->prox;
    (*primeiro)->prox = tmp->prox;

    if(tmp == (*ultimo)){
        (*ultimo) = (*primeiro);
    }
    int elemento = tmp->elemento;
    tmp->prox = NULL;
    free(tmp);
    tmp = NULL;
}


int main(){
    int valor;
    int cont = 0;
    Celula *primeiro = novaCelula(-1);
    Celula *ultimo = primeiro;

    while(scanf("%d",&valor) == 1){
        cont++;
        Celula *nova = novaCelula(valor);
        ultimo->prox = nova;
        ultimo = nova;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    removerInicio(&ultimo,&primeiro);


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