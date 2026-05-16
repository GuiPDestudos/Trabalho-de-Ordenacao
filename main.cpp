#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>
#include <utility>    // pair
#include <functional> // function

using namespace std;
using namespace chrono;

// =========================================================
// ESTRUTURA PARA RESULTADOS
// =========================================================

struct Resultado {
    long long comparacoes = 0;
    long long trocas      = 0;
    double    tempo       = 0.0;
};

// =========================================================
// FUNÇÃO PARA LER O ARQUIVO
// =========================================================

vector<int> lerArquivo(const string& nomeArquivo) {

    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro: nao foi possivel abrir o arquivo \""
             << nomeArquivo << "\"\n";
        return {};
    }

    vector<int> numeros;
    int valor;

    while (arquivo >> valor) {
        numeros.push_back(valor);
    }

    return numeros;
}

// =========================================================
// BUBBLE SORT
// =========================================================

Resultado bubbleSort(vector<int>& v) {

    Resultado r;
    int n = (int)v.size();

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) {           // -1: última passagem é desnecessária
        bool trocou = false;

        for (int j = 0; j < n - i - 1; j++) {
            r.comparacoes++;

            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                r.trocas++;
                trocou = true;
            }
        }

        if (!trocou) break;                      // vetor já ordenado: para cedo
    }

    r.tempo = duration<double>(high_resolution_clock::now() - inicio).count();
    return r;
}

// =========================================================
// SELECTION SORT
// =========================================================

Resultado selectionSort(vector<int>& v) {

    Resultado r;
    int n = (int)v.size();

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            r.comparacoes++;

            if (v[j] < v[menor]) {
                menor = j;
            }
        }

        if (menor != i) {
            swap(v[i], v[menor]);
            r.trocas++;
        }
    }

    r.tempo = duration<double>(high_resolution_clock::now() - inicio).count();
    return r;
}

// =========================================================
// INSERTION SORT
// =========================================================

Resultado insertionSort(vector<int>& v) {

    Resultado r;
    int n = (int)v.size();

    auto inicio = high_resolution_clock::now();

    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j     = i - 1;

        // Conta cada comparação feita pelo while (incluindo a que falha)
        while (j >= 0) {
            r.comparacoes++;

            if (v[j] > chave) {
                v[j + 1] = v[j];
                r.trocas++;
                j--;
            } else {
                break;
            }
        }

        v[j + 1] = chave;
    }

    r.tempo = duration<double>(high_resolution_clock::now() - inicio).count();
    return r;
}

// =========================================================
// HELPER: copia o vetor, ordena e devolve o resultado
// =========================================================

using FuncOrdenacao = function<Resultado(vector<int>&)>;

Resultado copiarEOrdenar(const vector<int>& dados, FuncOrdenacao algoritmo) {
    vector<int> copia = dados;
    return algoritmo(copia);
}

// =========================================================
// EXIBIR TABELA DE RESULTADOS
// =========================================================

void mostrarTabela(const vector<pair<string, Resultado>>& resultados) {

    const int cNome  = 18;
    const int cNum   = 15;

    cout << "\n";
    cout << left
         << setw(cNome) << "Algoritmo"
         << setw(cNum)  << "Comparacoes"
         << setw(cNum)  << "Trocas"
         << setw(cNum)  << "Tempo (s)"
         << "\n";

    cout << string(cNome + cNum * 3, '-') << "\n";

    for (const auto& [nome, r] : resultados) {
        cout << setw(cNome) << nome
             << setw(cNum)  << r.comparacoes
             << setw(cNum)  << r.trocas
             << fixed << setprecision(6)
             << setw(cNum)  << r.tempo
             << "\n";
    }

    cout << "\n";
}

// =========================================================
// GERAR CSV PARA GRÁFICOS
// =========================================================

void gerarCSV(const vector<pair<string, Resultado>>& resultados,
              const string& nomeCSV = "resultados_cpp.csv") {

    ofstream csv(nomeCSV);

    csv << "Algoritmo,Comparacoes,Trocas,Tempo\n";

    for (const auto& [nome, r] : resultados) {
        csv << nome << ","
            << r.comparacoes << ","
            << r.trocas << ","
            << r.tempo << "\n";
    }

    cout << "Arquivo \"" << nomeCSV << "\" gerado com sucesso!\n";
    cout << "Use Excel, LibreOffice ou Python para gerar os graficos.\n\n";
}

// =========================================================
// MAIN
// =========================================================

int main(int argc, char* argv[]) {

    // Permite passar o arquivo como argumento; usa aleatorio.txt por padrão
    string arquivo = (argc > 1) ? argv[1] : "/home/gui/Documentos/Trabalho-de-Ordenacao/aleatorio.txt";

    cout << "\nLendo arquivo: " << arquivo << " ...\n\n";

    vector<int> dados = lerArquivo(arquivo);

    if (dados.empty()) {
        cerr << "Nenhum numero foi carregado. Encerrando.\n";
        return 1;
    }

    cout << "Numeros carregados: " << dados.size() << "\n";

    // =====================================================
    // EXECUTA OS ALGORITMOS
    // =====================================================

    vector<pair<string, Resultado>> resultados = {
        { "Bubble Sort",    copiarEOrdenar(dados, bubbleSort)    },
        { "Selection Sort", copiarEOrdenar(dados, selectionSort) },
        { "Insertion Sort", copiarEOrdenar(dados, insertionSort) },
    };

    // =====================================================
    // EXIBE TABELA E GERA CSV
    // =====================================================

    mostrarTabela(resultados);
    gerarCSV(resultados);

    return 0;
}