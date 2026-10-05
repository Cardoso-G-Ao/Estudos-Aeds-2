#include <stdio.h>
#include <stdlib.h>

void InserirFinal(int vetor[],int *n,int capacidade,int novoValor)
{
  if(*n < capacidade){
    vetor[*n] =novoValor;
    (*n)++;
  }
}
int main()
{
 int vetor[5];
 int n = 0;
 for(int i = 0; i < 3;i++){
    scanf("%d",&vetor[i]);
    n++;
 }
 int novoValor;
 scanf("%d",&novoValor);
 InserirFinal(vetor,&n,5,novoValor);
 for(int j = 0; j < n ; j++){
    printf("%d ",vetor[j]);
 }
 printf("\n");
 return 0;

}
