import time
import matplotlib.pyplot as plt


# =========================================================
# FUNÇÃO PARA LER O ARQUIVO
# =========================================================

def ler_arquivo(nome_arquivo):

    numeros = []

    with open(nome_arquivo, "r") as arquivo:

        for linha in arquivo:

            linha = linha.strip()

            # Ignora linhas vazias
            if linha != "":
                numeros.append(int(linha))

    return numeros


# =========================================================
# BUBBLE SORT
# =========================================================

def bubble_sort(vetor):

    comparacoes = 0
    trocas = 0

    inicio = time.perf_counter()

    n = len(vetor)

    for i in range(n):

        for j in range(0, n - i - 1):

            comparacoes += 1

            if vetor[j] > vetor[j + 1]:

                vetor[j], vetor[j + 1] = vetor[j + 1], vetor[j]

                trocas += 1

    fim = time.perf_counter()

    tempo = fim - inicio

    return comparacoes, trocas, tempo


# =========================================================
# SELECTION SORT
# =========================================================

def selection_sort(vetor):

    comparacoes = 0
    trocas = 0

    inicio = time.perf_counter()

    n = len(vetor)

    for i in range(n):

        menor = i

        for j in range(i + 1, n):

            comparacoes += 1

            if vetor[j] < vetor[menor]:
                menor = j

        if menor != i:

            vetor[i], vetor[menor] = vetor[menor], vetor[i]

            trocas += 1

    fim = time.perf_counter()

    tempo = fim - inicio

    return comparacoes, trocas, tempo


# =========================================================
# INSERTION SORT
# =========================================================

def insertion_sort(vetor):

    comparacoes = 0
    trocas = 0

    inicio = time.perf_counter()

    for i in range(1, len(vetor)):

        chave = vetor[i]

        j = i - 1

        while j >= 0 and vetor[j] > chave:

            comparacoes += 1

            vetor[j + 1] = vetor[j]

            trocas += 1

            j -= 1

        # Conta a comparação final
        if j >= 0:
            comparacoes += 1

        vetor[j + 1] = chave

    fim = time.perf_counter()

    tempo = fim - inicio

    return comparacoes, trocas, tempo


# =========================================================
# FUNÇÃO PARA EXIBIR RESULTADOS
# =========================================================

def mostrar_resultado(nome, arquivo,
                      comparacoes, trocas, tempo):

    print("=" * 60)

    print(f"Algoritmo   : {nome}")
    print(f"Arquivo     : {arquivo}")
    print(f"Comparações : {comparacoes}")
    print(f"Trocas      : {trocas}")
    print(f"Tempo       : {tempo:.6f} segundos")

    print("=" * 60)
    print()


# =========================================================
# PROGRAMA PRINCIPAL
# =========================================================

arquivo = "aleatorio.txt"

print("\nLENDO DADOS DO ARQUIVO...\n")

# =========================================================
# PEGA OS VALORES DO ARQUIVO aleatorio.txt
# =========================================================

dados = ler_arquivo(arquivo)

print(f"Quantidade de números carregados: {len(dados)}\n")


# =========================================================
# BUBBLE SORT
# =========================================================

vetor_bubble = dados.copy()

resultado_bubble = bubble_sort(vetor_bubble)

mostrar_resultado(
    "Bubble Sort",
    arquivo,
    resultado_bubble[0],
    resultado_bubble[1],
    resultado_bubble[2]
)


# =========================================================
# SELECTION SORT
# =========================================================

vetor_selection = dados.copy()

resultado_selection = selection_sort(vetor_selection)

mostrar_resultado(
    "Selection Sort",
    arquivo,
    resultado_selection[0],
    resultado_selection[1],
    resultado_selection[2]
)


# =========================================================
# INSERTION SORT
# =========================================================

vetor_insertion = dados.copy()

resultado_insertion = insertion_sort(vetor_insertion)

mostrar_resultado(
    "Insertion Sort",
    arquivo,
    resultado_insertion[0],
    resultado_insertion[1],
    resultado_insertion[2]
)


# =========================================================
# TABELA RESUMO
# =========================================================

print("\nRESUMO DOS RESULTADOS\n")

print(f"{'Algoritmo':<20} {'Comparações':<15} {'Trocas':<15} {'Tempo(s)':<15}")

print("-" * 70)

print(f"{'Bubble Sort':<20} "
      f"{resultado_bubble[0]:<15} "
      f"{resultado_bubble[1]:<15} "
      f"{resultado_bubble[2]:<15.6f}")

print(f"{'Selection Sort':<20} "
      f"{resultado_selection[0]:<15} "
      f"{resultado_selection[1]:<15} "
      f"{resultado_selection[2]:<15.6f}")

print(f"{'Insertion Sort':<20} "
      f"{resultado_insertion[0]:<15} "
      f"{resultado_insertion[1]:<15} "
      f"{resultado_insertion[2]:<15.6f}")


# =========================================================
# DADOS DOS GRÁFICOS
# =========================================================

algoritmos = [
    "Bubble",
    "Selection",
    "Insertion"
]

comparacoes = [
    resultado_bubble[0],
    resultado_selection[0],
    resultado_insertion[0]
]

trocas = [
    resultado_bubble[1],
    resultado_selection[1],
    resultado_insertion[1]
]

tempos = [
    resultado_bubble[2],
    resultado_selection[2],
    resultado_insertion[2]
]


# =========================================================
# GRÁFICO - COMPARAÇÕES
# =========================================================

plt.figure(figsize=(8, 5))

plt.bar(algoritmos, comparacoes)

plt.title("Comparações dos Algoritmos")
plt.xlabel("Algoritmos")
plt.ylabel("Quantidade")

plt.show()


# =========================================================
# GRÁFICO - TROCAS
# =========================================================

plt.figure(figsize=(8, 5))

plt.bar(algoritmos, trocas)

plt.title("Trocas dos Algoritmos")
plt.xlabel("Algoritmos")
plt.ylabel("Quantidade")

plt.show()


# =========================================================
# GRÁFICO - TEMPO
# =========================================================

plt.figure(figsize=(8, 5))

plt.bar(algoritmos, tempos)

plt.title("Tempo de Execução")
plt.xlabel("Algoritmos")
plt.ylabel("Tempo (s)")

plt.show()