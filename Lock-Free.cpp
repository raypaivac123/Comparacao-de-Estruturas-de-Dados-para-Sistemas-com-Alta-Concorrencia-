#include <atomic>      // Biblioteca para operações atômicas  
#include <stdexcept>   // Biblioteca para lançamento de exceções  
#include <iostream>    // Biblioteca para entrada e saída  
#include <chrono>      // Biblioteca para medir tempo  


// Estrutura de um nó para armazenar valores na fila  
struct Node {  
    int valor;       // Valor armazenado no nó  
    Node* prox;     // Ponteiro para o próximo nó  

    Node(int v) : valor(v), prox(nullptr) {}  // Construtor inicializando o valor e próximo nó como nullptr  
};  

// Ponteiro atômico para a cabeça da fila  
std::atomic<Node*> head(nullptr);    

// Função de inserção sem bloqueio na fila  
void enqueue(int valor) {  
    Node* novo = new Node(valor);  // Cria um novo nó com o valor  
    Node* old_head;  


    do {  
        old_head = head.load();     // Carrega o ponteiro da cabeça atual  
        novo->prox = old_head;      // Define o próximo nó como o atual head  
    } while (!head.compare_exchange_weak(old_head, novo));  // Atualiza o head com CAS  
}  

// Função de remoção sem bloqueio na fila  
int dequeue() {  

    Node* old_head;  

    do {  
        old_head = head.load();     // Carrega o ponteiro da cabeça atual  
        if (old_head == nullptr) {  // Verifica se a fila está vazia  
            throw std::runtime_error("Fila vazia");  // Lança uma exceção se a fila estiver vazia  
        }  
    } while (!head.compare_exchange_weak(old_head, old_head->prox));  // Atualiza o head com CAS  
    
    int valor = old_head->valor;   // Pega o valor do nó removido  
    delete old_head;               // Libera a memória do nó removido  
    return valor;                  // Retorna o valor removido  
}  

// Função principal onde o programa começa a execução  
int main() {  
    const int NUM_OPS = 100000; // Número de operações a realizar  
    auto start = std::chrono::high_resolution_clock::now(); // Início da medição de tempo  

    // Realiza as operações de enqueue e dequeue  
    for (int i = 0; i < NUM_OPS; ++i) {  
        enqueue(i); // Adiciona valores à fila  
        dequeue();  // Remove valores da fila  
    }  

    auto end = std::chrono::high_resolution_clock::now(); // Fim da medição de tempo  
    std::chrono::duration<double, std::milli> elapsed = end - start; // Calcula o tempo decorrido  

    double latency = elapsed.count() / (NUM_OPS * 2); // Cálculo da latência média (ms)  
    double throughput = NUM_OPS * 2 / (elapsed.count() / 1000.0); // Calcula o throughput (ops/s)  

    std::cout << "Tempo de execução: " << elapsed.count() << " ms\n";  
    std::cout << "Latência média: " << latency << " ms/op\n"; // Exibe a latência média  
    std::cout << "Throughput: " << throughput << " ops/s\n"; // Exibe o throughput  

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso  

} 
