// =========================================================
// Disciplina: Estrutura de Dados
// Atividade: Algoritmos de Ordenação
//
// Algoritmos:
//   - Bubble Sort
//   - Selection Sort
//   - Insertion Sort
//
// O programa:
//   ✔ Lê os números do arquivo aleatorio.txt
//   ✔ Executa os algoritmos
//   ✔ Conta comparações
//   ✔ Conta trocas
//   ✔ Mede tempo de execução
//   ✔ Exibe resultados
//   ✔ Gera arquivo CSV para gráficos
//
// Linguagem: C++
// =========================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// =========================================================
// ESTRUTURA PARA RESULTADOS
// =========================================================

struct Resultado {

    long long comparacoes;
    long long trocas;
    double tempo;
};

// =========================================================
// FUNÇÃO PARA LER O ARQUIVO
// =========================================================

vector<int> lerArquivo(string nomeArquivo) {

    vector<int> numeros;

    ifstream arquivo(nomeArquivo);

    int valor;

    while (arquivo >> valor) {

        numeros.push_back(valor);
    }

    arquivo.close();

    return numeros;
}

// =========================================================
// BUBBLE SORT
// =========================================================

Resultado bubbleSort(vector<int>& vetor) {

    Resultado r;

    r.comparacoes = 0;
    r.trocas = 0;

    auto inicio = high_resolution_clock::now();

    int n = vetor.size();

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            r.comparacoes++;

            if (vetor[j] > vetor[j + 1]) {

                swap(vetor[j], vetor[j + 1]);

                r.trocas++;
            }
        }
    }

    auto fim = high_resolution_clock::now();

    duration<double> tempoGasto = fim - inicio;

    r.tempo = tempoGasto.count();

    return r;
}

// =========================================================
// SELECTION SORT
// =========================================================

Resultado selectionSort(vector<int>& vetor) {

    Resultado r;

    r.comparacoes = 0;
    r.trocas = 0;

    auto inicio = high_resolution_clock::now();

    int n = vetor.size();

    for (int i = 0; i < n; i++) {

        int menor = i;

        for (int j = i + 1; j < n; j++) {

            r.comparacoes++;

            if (vetor[j] < vetor[menor]) {

                menor = j;
            }
        }

        if (menor != i) {

            swap(vetor[i], vetor[menor]);

            r.trocas++;
        }
    }

    auto fim = high_resolution_clock::now();

    duration<double> tempoGasto = fim - inicio;

    r.tempo = tempoGasto.count();

    return r;
}

// =========================================================
// INSERTION SORT
// =========================================================

Resultado insertionSort(vector<int>& vetor) {

    Resultado r;

    r.comparacoes = 0;
    r.trocas = 0;

    auto inicio = high_resolution_clock::now();

    int n = vetor.size();

    for (int i = 1; i < n; i++) {

        int chave = vetor[i];

        int j = i - 1;

        while (j >= 0 && vetor[j] > chave) {

            r.comparacoes++;

            vetor[j + 1] = vetor[j];

            r.trocas++;

            j--;
        }

        if (j >= 0) {

            r.comparacoes++;
        }

        vetor[j + 1] = chave;
    }

    auto fim = high_resolution_clock::now();

    duration<double> tempoGasto = fim - inicio;

    r.tempo = tempoGasto.count();

    return r;
}

// =========================================================
// FUNÇÃO PARA MOSTRAR RESULTADOS
// =========================================================

void mostrarResultado(
    string algoritmo,
    string arquivo,
    Resultado r
) {

    cout << "====================================================\n";

    cout << "Algoritmo   : " << algoritmo << endl;
    cout << "Arquivo     : " << arquivo << endl;
    cout << "Comparacoes : " << r.comparacoes << endl;
    cout << "Trocas      : " << r.trocas << endl;

    cout << fixed << setprecision(6);

    cout << "Tempo       : " << r.tempo << " segundos\n";

    cout << "====================================================\n\n";
}

// =========================================================
// GERAR CSV PARA GRÁFICOS
// =========================================================

void gerarCSV(
    Resultado bubble,
    Resultado selection,
    Resultado insertion
) {

    ofstream csv("resultados.csv");

    csv << "Algoritmo,Comparacoes,Trocas,Tempo\n";

    csv << "Bubble Sort,"
        << bubble.comparacoes << ","
        << bubble.trocas << ","
        << bubble.tempo << "\n";

    csv << "Selection Sort,"
        << selection.comparacoes << ","
        << selection.trocas << ","
        << selection.tempo << "\n";

    csv << "Insertion Sort,"
        << insertion.comparacoes << ","
        << insertion.trocas << ","
        << insertion.tempo << "\n";

    csv.close();
}

// =========================================================
// MAIN
// =========================================================

int main() {

    string arquivo = "/home/gui/PyCharmMiscProject/aleatorio.txt";

    cout << "\nLENDO ARQUIVO...\n\n";

    // =====================================================
    // LÊ OS DADOS DO ARQUIVO
    // =====================================================

    vector<int> dados = lerArquivo(arquivo);

    if (dados.empty()) {

    cout << "\nNenhum numero foi carregado!\n";

    return 1;
    }

    cout << "Quantidade de numeros carregados: "
         << dados.size() << "\n\n";

    // =====================================================
    // BUBBLE SORT
    // =====================================================

    vector<int> vetorBubble = dados;

    Resultado resultadoBubble =
        bubbleSort(vetorBubble);

    mostrarResultado(
        "Bubble Sort",
        arquivo,
        resultadoBubble
    );

    // =====================================================
    // SELECTION SORT
    // =====================================================

    vector<int> vetorSelection = dados;

    Resultado resultadoSelection =
        selectionSort(vetorSelection);

    mostrarResultado(
        "Selection Sort",
        arquivo,
        resultadoSelection
    );

    // =====================================================
    // INSERTION SORT
    // =====================================================

    vector<int> vetorInsertion = dados;

    Resultado resultadoInsertion =
        insertionSort(vetorInsertion);

    mostrarResultado(
        "Insertion Sort",
        arquivo,
        resultadoInsertion
    );

    // =====================================================
    // TABELA RESUMO
    // =====================================================

    cout << "\nRESUMO DOS RESULTADOS\n\n";

    cout << left
         << setw(20) << "Algoritmo"
         << setw(20) << "Comparacoes"
         << setw(15) << "Trocas"
         << setw(15) << "Tempo(s)"
         << endl;

    cout << "-------------------------------------------------------------\n";

    cout << setw(20) << "Bubble Sort"
         << setw(20) << resultadoBubble.comparacoes
         << setw(15) << resultadoBubble.trocas
         << setw(15) << resultadoBubble.tempo
         << endl;

    cout << setw(20) << "Selection Sort"
         << setw(20) << resultadoSelection.comparacoes
         << setw(15) << resultadoSelection.trocas
         << setw(15) << resultadoSelection.tempo
         << endl;

    cout << setw(20) << "Insertion Sort"
         << setw(20) << resultadoInsertion.comparacoes
         << setw(15) << resultadoInsertion.trocas
         << setw(15) << resultadoInsertion.tempo
         << endl;

    // =====================================================
    // GERA CSV PARA GRÁFICOS
    // =====================================================

    gerarCSV(
        resultadoBubble,
        resultadoSelection,
        resultadoInsertion
    );

    cout << "\nArquivo resultados.csv gerado com sucesso!\n";

    cout << "\nUse o Excel, LibreOffice ou Python "
         << "para gerar os graficos.\n";

    return 0;
}