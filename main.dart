import 'dart:io';

// =========================================================
// CLASSE RESULTADO
// =========================================================

class Resultado {
  final String nome;
  final int comparacoes;
  final int trocas;
  final double tempo;

  const Resultado({
    required this.nome,
    required this.comparacoes,
    required this.trocas,
    required this.tempo,
  });
}

// =========================================================
// FUNÇÃO PARA LER O ARQUIVO
// =========================================================

List<int> lerArquivo(String nomeArquivo) {
  final arquivo = File(nomeArquivo);

  if (!arquivo.existsSync()) {
    stderr.writeln('Erro: arquivo "$nomeArquivo" não encontrado.');
    exit(1);
  }

  return arquivo
      .readAsLinesSync()
      .map((l) => l.trim())
      .where((l) => l.isNotEmpty)
      .map((l) {
        final valor = int.tryParse(l);
        if (valor == null) {
          stderr.writeln('Aviso: ignorando valor inválido "$l"');
        }
        return valor;
      })
      .whereType<int>()
      .toList();
}

// =========================================================
// BUBBLE SORT
// =========================================================

Resultado bubbleSort(List<int> v) {
  int comparacoes = 0;
  int trocas = 0;

  final tempo = Stopwatch()..start();

  final n = v.length;

  for (int i = 0; i < n - 1; i++) {
    bool trocou = false;

    for (int j = 0; j < n - i - 1; j++) {
      comparacoes++;

      if (v[j] > v[j + 1]) {
        final temp = v[j];
        v[j] = v[j + 1];
        v[j + 1] = temp;
        trocas++;
        trocou = true;
      }
    }

    if (!trocou) break; // vetor já ordenado: para cedo
  }

  tempo.stop();

  return Resultado(
    nome: 'Bubble Sort',
    comparacoes: comparacoes,
    trocas: trocas,
    tempo: tempo.elapsedMicroseconds / 1e6,
  );
}

// =========================================================
// SELECTION SORT
// =========================================================

Resultado selectionSort(List<int> v) {
  int comparacoes = 0;
  int trocas = 0;

  final tempo = Stopwatch()..start();

  final n = v.length;

  for (int i = 0; i < n - 1; i++) {
    int menor = i;

    for (int j = i + 1; j < n; j++) {
      comparacoes++;

      if (v[j] < v[menor]) {
        menor = j;
      }
    }

    if (menor != i) {
      final temp = v[i];
      v[i] = v[menor];
      v[menor] = temp;
      trocas++;
    }
  }

  tempo.stop();

  return Resultado(
    nome: 'Selection Sort',
    comparacoes: comparacoes,
    trocas: trocas,
    tempo: tempo.elapsedMicroseconds / 1e6,
  );
}

// =========================================================
// INSERTION SORT
// =========================================================

Resultado insertionSort(List<int> v) {
  int comparacoes = 0;
  int trocas = 0;

  final tempo = Stopwatch()..start();

  for (int i = 1; i < v.length; i++) {
    final chave = v[i];
    int j = i - 1;

    // Conta cada comparação, incluindo a que falha no while
    while (j >= 0) {
      comparacoes++;

      if (v[j] > chave) {
        v[j + 1] = v[j];
        trocas++;
        j--;
      } else {
        break;
      }
    }

    v[j + 1] = chave;
  }

  tempo.stop();

  return Resultado(
    nome: 'Insertion Sort',
    comparacoes: comparacoes,
    trocas: trocas,
    tempo: tempo.elapsedMicroseconds / 1e6,
  );
}

// =========================================================
// HELPER: copia a lista e executa o algoritmo
// =========================================================

typedef FuncOrdenacao = Resultado Function(List<int>);

Resultado copiarEOrdenar(List<int> dados, FuncOrdenacao algoritmo) {
  return algoritmo(List.of(dados));
}

// =========================================================
// MOSTRAR TABELA
// =========================================================

void mostrarTabela(List<Resultado> resultados) {
  const cNome  = 16;
  const cNum   = 14;

  print('\n${'─' * (cNome + cNum * 3)}');
  print(
    '${'Algoritmo'.padRight(cNome)}'
    '${'Comparações'.padRight(cNum)}'
    '${'Trocas'.padRight(cNum)}'
    '${'Tempo (s)'.padRight(cNum)}',
  );
  print('${'─' * (cNome + cNum * 3)}');

  for (final r in resultados) {
    print(
      '${r.nome.padRight(cNome)}'
      '${r.comparacoes.toString().padRight(cNum)}'
      '${r.trocas.toString().padRight(cNum)}'
      '${r.tempo.toStringAsFixed(6).padRight(cNum)}',
    );
  }

  print('${'─' * (cNome + cNum * 3)}\n');
}

// =========================================================
// GERAR CSV
// =========================================================

void gerarCSV(List<Resultado> resultados, {String nomeCSV = 'resultados_dart.csv'}) {
  final buffer = StringBuffer();

  buffer.writeln('Algoritmo,Comparacoes,Trocas,Tempo');

  for (final r in resultados) {
    buffer.writeln('${r.nome},${r.comparacoes},${r.trocas},${r.tempo}');
  }

  File(nomeCSV).writeAsStringSync(buffer.toString());

  print('Arquivo "$nomeCSV" gerado com sucesso!');
  print('Use Excel, LibreOffice, Google Sheets ou Python para gerar gráficos.\n');
}

// =========================================================
// MAIN
// =========================================================

void main(List<String> args) {
  // Permite passar o arquivo como argumento; usa aleatorio.txt por padrão
  final nomeArquivo = args.isNotEmpty ? args[0] : 'aleatorio.txt';

  print('\nLendo arquivo: $nomeArquivo ...\n');

  final dados = lerArquivo(nomeArquivo);

  print('Números carregados: ${dados.length}');

  // -------------------------------------------------------
  // Executa os algoritmos
  // -------------------------------------------------------

  final resultados = [
    copiarEOrdenar(dados, bubbleSort),
    copiarEOrdenar(dados, selectionSort),
    copiarEOrdenar(dados, insertionSort),
  ];

  // -------------------------------------------------------
  // Exibe tabela e gera CSV
  // -------------------------------------------------------

  mostrarTabela(resultados);
  gerarCSV(resultados);
}