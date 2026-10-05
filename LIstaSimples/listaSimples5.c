#include <stdio.h>
#include <stdlib.h>

void RemoverPosiçãoEscolhida(int pos,int vetor[], int *n){
    if (pos < 0 || pos >= *n)
    {
        printf("Erro\n");
        return;
    }
    for (int i = pos; i < *n - 1; i++)
    {
        vetor[i] = vetor[i + 1];
    }
    (*n)--;
}

int main()
{
    int vetor[5];
    int n = 0;
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &vetor[i]);
        n++;
    }
    int posicao;
    scanf("%d", &posicao);
    RemoverPosiçãoEscolhida(posicao, vetor, &n);
    for (int j = 0; j < n; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;

}
