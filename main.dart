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
//   ✔ Mostra tabela comparativa
//   ✔ Gera arquivo CSV para gráficos
//
// Linguagem: Dart
// =========================================================

import 'dart:io';

// =========================================================
// CLASSE RESULTADO
// =========================================================

class Resultado {
  int comparacoes;
  int trocas;
  double tempo;

  Resultado(this.comparacoes, this.trocas, this.tempo);
}

// =========================================================
// FUNÇÃO PARA LER O ARQUIVO
// =========================================================

List<int> lerArquivo(String nomeArquivo) {
  File arquivo = File(nomeArquivo);

  List<String> linhas = arquivo.readAsLinesSync();

  List<int> numeros = [];

  for (String linha in linhas) {
    linha = linha.trim();

    if (linha.isNotEmpty) {
      numeros.add(int.parse(linha));
    }
  }

  return numeros;
}

// =========================================================
// BUBBLE SORT
// =========================================================

Resultado bubbleSort(List<int> vetor) {
  int comparacoes = 0;
  int trocas = 0;

  Stopwatch tempo = Stopwatch();
  tempo.start();

  int n = vetor.length;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      comparacoes++;

      if (vetor[j] > vetor[j + 1]) {
        int temp = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = temp;

        trocas++;
      }
    }
  }

  tempo.stop();

  double segundos = tempo.elapsedMicroseconds / 1000000;

  return Resultado(comparacoes, trocas, segundos);
}

// =========================================================
// SELECTION SORT
// =========================================================

Resultado selectionSort(List<int> vetor) {
  int comparacoes = 0;
  int trocas = 0;

  Stopwatch tempo = Stopwatch();
  tempo.start();

  int n = vetor.length;

  for (int i = 0; i < n; i++) {
    int menor = i;

    for (int j = i + 1; j < n; j++) {
      comparacoes++;

      if (vetor[j] < vetor[menor]) {
        menor = j;
      }
    }

    if (menor != i) {
      int temp = vetor[i];
      vetor[i] = vetor[menor];
      vetor[menor] = temp;

      trocas++;
    }
  }

  tempo.stop();

  double segundos = tempo.elapsedMicroseconds / 1000000;

  return Resultado(comparacoes, trocas, segundos);
}

// =========================================================
// INSERTION SORT
// =========================================================

Resultado insertionSort(List<int> vetor) {
  int comparacoes = 0;
  int trocas = 0;

  Stopwatch tempo = Stopwatch();
  tempo.start();

  for (int i = 1; i < vetor.length; i++) {
    int chave = vetor[i];

    int j = i - 1;

    while (j >= 0 && vetor[j] > chave) {
      comparacoes++;

      vetor[j + 1] = vetor[j];

      trocas++;

      j--;
    }

    if (j >= 0) {
      comparacoes++;
    }

    vetor[j + 1] = chave;
  }

  tempo.stop();

  double segundos = tempo.elapsedMicroseconds / 1000000;

  return Resultado(comparacoes, trocas, segundos);
}

// =========================================================
// MOSTRAR RESULTADOS
// =========================================================

void mostrarResultado(
    String algoritmo,
    String arquivo,
    Resultado r
    ) {

  print("====================================================");

  print("Algoritmo   : $algoritmo");
  print("Arquivo     : $arquivo");
  print("Comparações : ${r.comparacoes}");
  print("Trocas      : ${r.trocas}");
  print("Tempo       : ${r.tempo.toStringAsFixed(6)} segundos");

  print("====================================================\n");
}

// =========================================================
// GERAR CSV
// =========================================================

void gerarCSV(
    Resultado bubble,
    Resultado selection,
    Resultado insertion
    ) {

  File arquivo = File("resultados.csv");

  String conteudo = "";

  conteudo += "Algoritmo,Comparacoes,Trocas,Tempo\n";

  conteudo +=
  "Bubble Sort,"
      "${bubble.comparacoes},"
      "${bubble.trocas},"
      "${bubble.tempo}\n";

  conteudo +=
  "Selection Sort,"
      "${selection.comparacoes},"
      "${selection.trocas},"
      "${selection.tempo}\n";

  conteudo +=
  "Insertion Sort,"
      "${insertion.comparacoes},"
      "${insertion.trocas},"
      "${insertion.tempo}\n";

  arquivo.writeAsStringSync(conteudo);
}

// =========================================================
// MAIN
// =========================================================

void main() {

  String nomeArquivo = "aleatorio.txt";

  print("\nLENDO ARQUIVO...\n");

  // =======================================================
  // LÊ OS DADOS DO ARQUIVO aleatorio.txt
  // =======================================================

  List<int> dados = lerArquivo(nomeArquivo);

  print("Quantidade de números carregados: ${dados.length}\n");

  // =======================================================
  // BUBBLE SORT
  // =======================================================

  List<int> vetorBubble = List.from(dados);

  Resultado resultadoBubble = bubbleSort(vetorBubble);

  mostrarResultado(
      "Bubble Sort",
      nomeArquivo,
      resultadoBubble
  );

  // =======================================================
  // SELECTION SORT
  // =======================================================

  List<int> vetorSelection = List.from(dados);

  Resultado resultadoSelection =
  selectionSort(vetorSelection);

  mostrarResultado(
      "Selection Sort",
      nomeArquivo,
      resultadoSelection
  );

  // =======================================================
  // INSERTION SORT
  // =======================================================

  List<int> vetorInsertion = List.from(dados);

  Resultado resultadoInsertion =
  insertionSort(vetorInsertion);

  mostrarResultado(
      "Insertion Sort",
      nomeArquivo,
      resultadoInsertion
  );

  // =======================================================
  // TABELA RESUMO
  // =======================================================

  print("\nRESUMO DOS RESULTADOS\n");

  print(
      "Algoritmo\t\tComparações\tTrocas\t\tTempo(s)"
  );

  print(
      "--------------------------------------------------------------"
  );

  print(
      "Bubble Sort\t\t"
          "${resultadoBubble.comparacoes}\t\t"
          "${resultadoBubble.trocas}\t\t"
          "${resultadoBubble.tempo.toStringAsFixed(6)}"
  );

  print(
      "Selection Sort\t"
          "${resultadoSelection.comparacoes}\t\t"
          "${resultadoSelection.trocas}\t\t"
          "${resultadoSelection.tempo.toStringAsFixed(6)}"
  );

  print(
      "Insertion Sort\t"
          "${resultadoInsertion.comparacoes}\t\t"
          "${resultadoInsertion.trocas}\t\t"
          "${resultadoInsertion.tempo.toStringAsFixed(6)}"
  );

  // =======================================================
  // GERA CSV
  // =======================================================

  gerarCSV(
      resultadoBubble,
      resultadoSelection,
      resultadoInsertion
  );

  print("\nArquivo resultados.csv gerado com sucesso!");

  print(
      "\nUse Excel, LibreOffice, Google Sheets "
          "ou Flutter para gerar os gráficos."
  );
}