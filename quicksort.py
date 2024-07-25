import matplotlib.pyplot as plt
import numpy as np

# Carregar dados do arquivo
file_path = 'QuickSortIteracoesCasoMedio.txt'
try:
    data = np.loadtxt(file_path)
except OSError as e:
    print(f"Erro ao carregar o arquivo: {e}")
    exit(1)

# Tamanhos dos arrays usados no experimento
array_sizes = [5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000]

# Verificar se os dados foram carregados corretamente
if data.size == 0:
    print("Erro: O arquivo está vazio ou não pôde ser lido corretamente.")
    exit(1)

# Calcular o número médio de iterações para cada tamanho de array
try:
    mean_iterations = np.mean(data.reshape(len(array_sizes), -1), axis=1)
except ValueError as e:
    print(f"Erro ao processar os dados: {e}")
    exit(1)

# Plotando os resultados
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, mean_iterations, marker='o')
plt.title('Número Médio de Iterações para QuickSort')
plt.xlabel('Tamanho do Array')
plt.ylabel('Número de Iterações')
plt.grid(True)
plt.xticks(array_sizes)
plt.savefig('quicksort_iterations.png')
plt.show()
