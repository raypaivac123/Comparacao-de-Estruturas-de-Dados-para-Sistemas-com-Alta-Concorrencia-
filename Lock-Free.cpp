#include <atomic>      // Biblioteca para opera��es at�micas  
#include <stdexcept>   // Biblioteca para lan�amento de exce��es  
#include <iostream>    // Biblioteca para entrada e sa�da  
#include <chrono>      // Biblioteca para medir tempo  


// Estrutura de um n� para armazenar valores na fila  
struct Node {  
    int valor;       // Valor armazenado no n�  
    Node* prox;     // Ponteiro para o pr�ximo n�  

    Node(int v) : valor(v), prox(nullptr) {}  // Construtor inicializando o valor e pr�ximo n� como nullptr  
};  

// Ponteiro at�mico para a cabe�a da fila  
std::atomic<Node*> head(nullptr);    

// Fun��o de inser��o sem bloqueio na fila  
void enqueue(int valor) {  
    Node* novo = new Node(valor);  // Cria um novo n� com o valor  
    Node* old_head;  


    do {  
        old_head = head.load();     // Carrega o ponteiro da cabe�a atual  
        novo->prox = old_head;      // Define o pr�ximo n� como o atual head  
    } while (!head.compare_exchange_weak(old_head, novo));  // Atualiza o head com CAS  
}  

// Fun��o de remo��o sem bloqueio na fila  
int dequeue() {  

    Node* old_head;  

    do {  
        old_head = head.load();     // Carrega o ponteiro da cabe�a atual  
        if (old_head == nullptr) {  // Verifica se a fila est� vazia  
            throw std::runtime_error("Fila vazia");  // Lan�a uma exce��o se a fila estiver vazia  
        }  
    } while (!head.compare_exchange_weak(old_head, old_head->prox));  // Atualiza o head com CAS  
    
    int valor = old_head->valor;   // Pega o valor do n� removido  
    delete old_head;               // Libera a mem�ria do n� removido  
    return valor;                  // Retorna o valor removido  
}  

// Fun��o principal onde o programa come�a a execu��o  
int main() {  
    const int NUM_OPS = 100000; // N�mero de opera��es a realizar  
    auto start = std::chrono::high_resolution_clock::now(); // In�cio da medi��o de tempo  

    // Realiza as opera��es de enqueue e dequeue  
    for (int i = 0; i < NUM_OPS; ++i) {  
        enqueue(i); // Adiciona valores � fila  
        dequeue();  // Remove valores da fila  
    }  

    auto end = std::chrono::high_resolution_clock::now(); // Fim da medi��o de tempo  
    std::chrono::duration<double, std::milli> elapsed = end - start; // Calcula o tempo decorrido  

    double latency = elapsed.count() / (NUM_OPS * 2); // C�lculo da lat�ncia m�dia (ms)  
    double throughput = NUM_OPS * 2 / (elapsed.count() / 1000.0); // Calcula o throughput (ops/s)  

    std::cout << "Tempo de execu��o: " << elapsed.count() << " ms\n";  
    std::cout << "Lat�ncia m�dia: " << latency << " ms/op\n"; // Exibe a lat�ncia m�dia  
    std::cout << "Throughput: " << throughput << " ops/s\n"; // Exibe o throughput  

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso  

} 
