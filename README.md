# 🚀 Comparação de Fila Lock-Based e Lock-Free em C++

Este repositório contém duas implementações de filas em C++ para comparar o desempenho de operações de inserção e remoção utilizando diferentes abordagens: uma com bloqueio (`Lock-Based`) e outra sem bloqueio (`Lock-Free`).

## 📂 Arquivos do Projeto

- **`Lock-Based.cpp`**: Implementação usando mutex.
- **`Lock-Free.cpp`**: Implementação usando operações atômicas (lock-free).

## 🎯 Objetivo

O objetivo é medir o desempenho em termos de:

- **Latência**: Tempo médio por operação.
- **Throughput**: Operações por segundo.

## 📊 Resultados

| Implementação | Tempo de Execução (ms) | Latência Média (ms/op) | Throughput (ops/s) |
|---------------|------------------------|------------------------|--------------------|
| Lock-Free     | 6.73502                | 3.36751e-05            | 2.96955e+07        |
| Lock-Based    | 9.21294                | 4.60647e-05            | 2.17086e+07        |

## 🔧 Como Executar

### Pré-requisitos

- Compilador C++ com suporte ao C++11 ou superior (e.g. `g++`, `clang`).
- CMake (opcional, se você preferir usar um sistema de build).

### Compilar e Executar

#### Lock-Based:
```bash
g++ -std=c++11 Lock-Based.cpp -o lock_based
./lock_based
```

#### Lock-Free:
```bash
g++ -std=c++11 Lock-Free.cpp -o lock_free
./lock_free
```

## 📈 Saída do Programa

Os programas mostram:

- **Tempo total de execução**.
- **Latência média** por operação.
- **Throughput** em operações por segundo.

## 📜 Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
