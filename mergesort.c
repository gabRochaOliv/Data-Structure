#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variável global para contar iterações
int iteracoes;

// Função para misturar o vetor
void mistureVetor(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if ((rand() / (double)RAND_MAX) < 0.5)
        {
            int j = (int)((n - 1) * (rand() / (double)RAND_MAX));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

// Função para mesclar dois subarrays
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        iteracoes++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        iteracoes++;
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        iteracoes++;
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Implementação do MergeSort
void mergesort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main()
{
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Abrir arquivo para armazenar os resultados
    FILE *fp_merge = fopen("MergeSortIteracoesCasoMedio.txt", "w");
    if (fp_merge == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    srand(time(0)); // Iniciar os números aleatórios

    // Loop pelos tamanhos de vetor
    for (int i = 0; i < num_tamanhos; i++)
    {
        int tam = tamanhos[i];

        int *arr = (int *)malloc(tam * sizeof(int));
        if (arr == NULL)
        {
            printf("Erro ao alocar memória.\n");
            fclose(fp_merge);
            return 1;
        }

        // Preencher o array com valores crescentes
        for (int j = 0; j < tam; j++)
        {
            arr[j] = j;
        }

        // Executar 30 repetições para obter o caso médio
        for (int j = 0; j < 30; j++)
        {
            mistureVetor(arr, tam);
            iteracoes = 0;

            // MergeSort
            mergesort(arr, 0, tam - 1);
            fprintf(fp_merge, "%d ", iteracoes);
        }
        fprintf(fp_merge, "\n");
        free(arr); // Liberar memória do array
    }

    // Fechar arquivo
    fclose(fp_merge);

    return 0;
}
