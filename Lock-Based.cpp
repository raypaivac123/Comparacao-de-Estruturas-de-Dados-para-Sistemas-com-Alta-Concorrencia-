#include <iostream>   // Biblioteca para entrada e sa�da de dados  
#include <queue>      // Biblioteca para a estrutura de dados "queue"  
#include <mutex>      // Biblioteca para uso de mutex  
#include <stdexcept>  // Biblioteca para lan�ar exce��es  
#include <chrono>     // Biblioteca para medir tempo 

std::queue<int> filaDeInteiros;   // Declara��o de uma fila para armazenar inteiros  
std::mutex mutexFila;              // Declara��o de um mutex para garantir acesso seguro � fila  

// Fun��o para adicionar um valor � fila  
void adicionarValor(int novoValor) {  
    std::lock_guard<std::mutex> bloqueio(mutexFila);  // Garante acesso exclusivo � fila  
    filaDeInteiros.push(novoValor);  // Insere o novo valor na fila  
}  

// Fun��o para remover um valor da fila  
int removerValor() {  
    std::lock_guard<std::mutex> bloqueio(mutexFila);  // Garante acesso seguro durante a remo��o  
    if (filaDeInteiros.empty()) {                        // Verifica se a fila est� vazia  
        throw std::runtime_error("Fila vazia");         // Lan�a uma exce��o se a fila estiver vazia  
    }  

    int valorRemovido = filaDeInteiros.front();         // Obt�m o valor do in�cio da fila  
    filaDeInteiros.pop();                                // Remove o valor da fila  
    return valorRemovido;                                // Retorna o valor removido  
}  

// Fun��o principal onde o programa come�a a execu��o  
int main() {  
    const int NUM_OPS = 100000; // N�mero de opera��es a realizar  
    auto start = std::chrono::high_resolution_clock::now(); // In�cio da medi��o de tempo  

    // Realiza as opera��es de adicionar e remover valores da fila  
    for (int i = 0; i < NUM_OPS; ++i) {  
        adicionarValor(i); // Adiciona valores � fila  
        removerValor();     // Remove valores da fila  
    }  

    auto end = std::chrono::high_resolution_clock::now(); // Fim da medi��o de tempo  
    std::chrono::duration<double, std::milli> elapsed = end - start; // Calcula o tempo decorrido  

    double latency = elapsed.count() / (NUM_OPS * 2); // C�lculo da lat�ncia m�dia (ms/op)  
    double throughput = NUM_OPS * 2 / (elapsed.count() / 1000.0); // Calcula o throughput (ops/s)  

    std::cout << "Tempo de execu��o: " << elapsed.count() << " ms\n";  
    std::cout << "Lat�ncia m�dia: " << latency << " ms/op\n"; // Exibe a lat�ncia m�dia  
    std::cout << "Throughput: " << throughput << " ops/s\n"; // Exibe o throughput  

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso  

} 
