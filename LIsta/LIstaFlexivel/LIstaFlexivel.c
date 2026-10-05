#include <stdio.h>
#include <stdlib.h>




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
    for(int i = 0; i < cont;i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");
    free(vetor);
    return 0;

}