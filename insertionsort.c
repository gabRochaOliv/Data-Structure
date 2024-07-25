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

// Implementação do Insertion Sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            iteracoes++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        iteracoes++;
        arr[j + 1] = key;
    }
}

int main()
{
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Abrir arquivo para armazenar os resultados
    FILE *fp_insertion = fopen("InsertionSortIteracoesCasoMedio.txt", "w");
    if (fp_insertion == NULL)
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
            fclose(fp_insertion);
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

            // Insertion Sort
            insertionSort(arr, tam);
            fprintf(fp_insertion, "%d ", iteracoes);
        }
        fprintf(fp_insertion, "\n");
        free(arr); // Liberar memória do array
    }

    // Fechar arquivo
    fclose(fp_insertion);

    return 0;
}
