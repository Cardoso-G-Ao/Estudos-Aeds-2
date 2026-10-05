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
void inserirInicio(int valor,Celula **primeiro ,Celula **ultimo){
    int valorNovo;
    scanf("%d",&valorNovo);
    Celula *tmp = novaCelula(valorNovo);
    tmp->prox = (*primeiro)->prox;
    (*primeiro)->prox = tmp;
    if((*primeiro) == (*ultimo)){
        (*ultimo) = tmp;
    }
    tmp = NULL;
}


int main(){
    int valor ;
    int cont = 0 ;
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
    inserirInicio(valor,&primeiro,&ultimo);

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