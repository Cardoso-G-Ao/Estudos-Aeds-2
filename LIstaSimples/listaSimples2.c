#include <stdio.h>
#include <stdlib.h>

void removerInicio(int vetor[]){
    int n = 5;
    int resp = vetor[0];
    n--;
    for (int i = 0; i < n; i++){
    vetor[i] = vetor[i+1];
    }
}
int main(){
    int vetor[5];
    for(int i = 0; i < 5;i++){
         scanf("%d",&vetor[i]);
    }
    removerInicio(vetor);
    for(int j =  0;j < 5;j++){
        printf("%d ",vetor[j]);
    }
    printf("\n");
    return 0;
}