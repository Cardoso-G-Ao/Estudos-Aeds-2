#include <stdio.h>
#include <stdlib.h>

typedef struct CelulaDupla
{
    int elemento;
    struct CelulaDupla *prox, *ant;
} CelulaDupla;

CelulaDupla *novaCelula(int elemento)
{
    CelulaDupla *nova = (CelulaDupla *)malloc(sizeof(CelulaDupla));
    nova->elemento = elemento;
    nova->prox = nova->ant = NULL;
    return nova;
}

void removerInicio(CelulaDupla **primeiro,CelulaDupla **ultimo){
    if((*primeiro)==(*ultimo)){
       printf("erro");
       return;
    }
    CelulaDupla *tmp = (*primeiro);
    (*primeiro) = (*primeiro)->prox ;
    if(tmp == (*ultimo)){
    (*ultimo) = (*primeiro);
    }
    int elemento  = (*primeiro)->elemento;
    tmp->prox = (*primeiro)->ant = NULL;
    tmp->ant = NULL;
    free(tmp);
    tmp = NULL;

}   

int main()
{
    int valor;
    int cont = 0;
    CelulaDupla *primeiro = NULL;
    CelulaDupla *ultimo = NULL;
    while (scanf("%d", &valor) == 1)
    {
        cont++;
        CelulaDupla *nova = novaCelula(valor);
        if (primeiro == NULL)
        {
            primeiro = nova;
            ultimo = nova;
        }
        else
        {
            ultimo->prox = nova;
            nova->ant = ultimo;
            ultimo = nova;
        }
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    removerInicio(&primeiro,&ultimo);


     CelulaDupla *atual = primeiro;
    while (atual != NULL) {
        printf("%d ", atual->elemento);
        atual = atual->prox; 
    }
    printf("\n");

    atual = primeiro;
    while (atual != NULL) {
        CelulaDupla *proxima = atual->prox; 
        free(atual);                   
        atual = proxima;               
    }

    return 0;
}