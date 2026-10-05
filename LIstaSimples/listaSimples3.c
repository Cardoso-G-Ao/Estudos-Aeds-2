#include <stdio.h>
#include <stdlib.h>

void removerFinal(int *n)
{
    if(*n > 0){
        (*n)--;
    }
}
int main()
{
    int n = 5;
    int vetor[5];
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &vetor[i]);
    }
    removerFinal(&n);
    for (int j = 0; j < n; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}