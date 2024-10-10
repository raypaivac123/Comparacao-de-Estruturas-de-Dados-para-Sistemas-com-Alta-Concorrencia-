#include <iostream>   // Biblioteca para entrada e saída de dados  
#include <queue>      // Biblioteca para a estrutura de dados "queue"  
#include <mutex>      // Biblioteca para uso de mutex  
#include <stdexcept>  // Biblioteca para lançar exceções  
#include <chrono>     // Biblioteca para medir tempo 

std::queue<int> filaDeInteiros;   // Declaração de uma fila para armazenar inteiros  
std::mutex mutexFila;              // Declaração de um mutex para garantir acesso seguro à fila  

// Função para adicionar um valor à fila  
void adicionarValor(int novoValor) {  
    std::lock_guard<std::mutex> bloqueio(mutexFila);  // Garante acesso exclusivo à fila  
    filaDeInteiros.push(novoValor);  // Insere o novo valor na fila  
}  

// Função para remover um valor da fila  
int removerValor() {  
    std::lock_guard<std::mutex> bloqueio(mutexFila);  // Garante acesso seguro durante a remoção  
    if (filaDeInteiros.empty()) {                        // Verifica se a fila está vazia  
        throw std::runtime_error("Fila vazia");         // Lança uma exceção se a fila estiver vazia  
    }  

    int valorRemovido = filaDeInteiros.front();         // Obtém o valor do início da fila  
    filaDeInteiros.pop();                                // Remove o valor da fila  
    return valorRemovido;                                // Retorna o valor removido  
}  

// Função principal onde o programa começa a execução  
int main() {  
    const int NUM_OPS = 100000; // Número de operações a realizar  
    auto start = std::chrono::high_resolution_clock::now(); // Início da medição de tempo  

    // Realiza as operações de adicionar e remover valores da fila  
    for (int i = 0; i < NUM_OPS; ++i) {  
        adicionarValor(i); // Adiciona valores à fila  
        removerValor();     // Remove valores da fila  
    }  

    auto end = std::chrono::high_resolution_clock::now(); // Fim da medição de tempo  
    std::chrono::duration<double, std::milli> elapsed = end - start; // Calcula o tempo decorrido  

    double latency = elapsed.count() / (NUM_OPS * 2); // Cálculo da latência média (ms/op)  
    double throughput = NUM_OPS * 2 / (elapsed.count() / 1000.0); // Calcula o throughput (ops/s)  

    std::cout << "Tempo de execução: " << elapsed.count() << " ms\n";  
    std::cout << "Latência média: " << latency << " ms/op\n"; // Exibe a latência média  
    std::cout << "Throughput: " << throughput << " ops/s\n"; // Exibe o throughput  

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso  

} 
