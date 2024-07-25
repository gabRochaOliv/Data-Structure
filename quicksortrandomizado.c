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

// Função para trocar dois elementos
void troca(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Particionamento do QuickSort com pivô aleatório
int particiona(int arr[], int low, int high)
{
    int random_index = low + rand() % (high - low + 1);
    troca(&arr[random_index], &arr[high]); // Trocar pivô aleatório com o último elemento
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        iteracoes++;
        if (arr[j] < pivot)
        {
            i++;
            troca(&arr[i], &arr[j]);
        }
    }
    troca(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Implementação do QuickSort
void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = particiona(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main()
{
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Abrir arquivo para armazenar os resultados
    FILE *fp_quick_random = fopen("QuickSortRandomizadoIteracoesCasoMedio.txt", "w");
    if (fp_quick_random == NULL)
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
            fclose(fp_quick_random);
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

            // QuickSort Randomizado
            quicksort(arr, 0, tam - 1);
            fprintf(fp_quick_random, "%d ", iteracoes);
        }
        fprintf(fp_quick_random, "\n");
        free(arr); // Liberar memória do array
    }

    // Fechar arquivo
    fclose(fp_quick_random);

    return 0;
}
