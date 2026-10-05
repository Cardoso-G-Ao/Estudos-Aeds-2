#include <stdio.h>
#include <stdlib.h>

void removerInicio(int **vetor, int *cont){
   if(*cont <= 0){
    return;
   }
   (*vetor)[0]--;
   for(int i = 0 ; i < *cont - 1;i++){
        (*vetor)[i] = (*vetor)[i + 1];
   }
   (*cont)--;
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
    removerInicio(&vetor,&cont);
    for(int i = 0; i < cont;i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");
    free(vetor);
    return 0;
}