#include <stdio.h>
#include <stdlib.h>

void removerValor(int **vetor, int *cont,int retirar){
    int i = 0;
    int encontrado = 0;
    while(i < *cont && (*vetor)[i] != retirar){
        i++;
    }
    if(i < *cont){
        for(int j = i ; j < *cont - 1;j++ ){
            (*vetor)[j] = (*vetor)[j + 1];
        }
        encontrado = 1;
    }
    if(encontrado){
        (*cont)--;
    }
    if (*cont > 0) {
        int *temp = (int*) realloc(*vetor, (*cont) * sizeof(int));
        if (temp != NULL) {
            *vetor = temp;
        }
    } else {
        free(*vetor);
        *vetor = NULL;
    }
}

int main(){
    int *vetor = NULL;
    int valor;
    int cont = 0;
    int retirar;
    scanf("%d",&retirar);
    while(scanf("%d",&valor) == 1){
        cont++;
        int *temp = (int*)realloc(vetor,cont * sizeof(int));
        if(temp == NULL){
            free(vetor);
            return 1;
        }
        vetor = temp;
        vetor[cont - 1] = valor;
    }
    removerValor(&vetor,&cont,retirar);
    for(int i = 0; i < cont;i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");
    free(vetor);
    return 0;
}