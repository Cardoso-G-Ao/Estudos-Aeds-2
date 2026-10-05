#include <stdio.h>
#include <stdlib.h>

void removerValor(int n ,int vetor[]){
    for(int i = 0;i < 5;i++){
        if(vetor[i] == n){
            vetor[i] = 0;
        }
    }
}
int main(){
    int vetor[5];
    int n;
    scanf("%d",&n);
    for(int i = 0; i < 5;i++){
         scanf("%d",&vetor[i]);
    }
    for(int k =0; k< 5; k++){
         printf("%d ",vetor[k]);
    }
    printf("\n");
    removerValor(n,vetor);
    for(int j =  0;j < 5;j++){
        printf("%d ",vetor[j]);
    }
    printf("\n");
    return 0;
}