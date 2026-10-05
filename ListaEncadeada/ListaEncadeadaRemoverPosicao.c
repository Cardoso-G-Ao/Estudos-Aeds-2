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
void removerPosicao(Celula **ultimo,Celula **primeiro){
    if((*ultimo)==(*primeiro)){
        printf("erro");
        return;
    }
    int novoValor;
    scanf("%d",&novoValor);
    Celula *i = (*primeiro);
    for(int j = 0 ; j < novoValor;j++, i = i->prox);
    if(i->prox == NULL){
        printf("erro\n");
        return;
    }
    Celula *tmp = i->prox;
    int elementoRemovido = tmp->elemento; 
    i->prox = tmp->prox;
    if(i->prox == NULL){
        (*ultimo) = i;
    }
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

    removerPosicao(&ultimo,&primeiro);


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