#include "lib.hpp"
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/* 
    Se quiser crie funcoes e variaveis aqui    
*/

int caminho_anterior(int i, stack<int> anteriores) {
    int j, caminho = 1;
    
    while (!anteriores.empty()) {
        j = anteriores.top();
        anteriores.pop();
        
        if (has_edge(j, i)) {
            caminho = caminho + caminho_anterior(j, anteriores);
        }
    }
    
    return caminho;
}



int caminho_posterior(int i, stack<int> posteriores) {
    int j, caminho = 1;
    
    while (!posteriores.empty()) {
        j = posteriores.top();
        posteriores.pop();
        
        if (has_edge(i, j)) {
            caminho = caminho + caminho_posterior(j, posteriores);
        }
    }
    
    return caminho;
}



// has_edge(int i, int j): retorna true se há tirolesa do monte i para o monte j,
//                         nesse sentido, e false caso contrario.
vector<int> solve(int n) {
    vector<int> path;
    int aponta[n];
    int apontado[n];
    stack<int> anteriores;
    stack<int> posteriores;
    int mca = 0, mcp = 0;
    
    
    // Inicializamos duas listas que indicam quais elementos apontam pro monte 1 
    // e quais são apontados pelo monte 1
    for (int i = 0; i < n; i++) {
        aponta[i] = 0;
        apontado[i] = 0;
    }
    
    
    
    // Inicializamos uma pilha de montes anteriores (apontam)
    // e posteriores (apontados) ao monte 1
    for (int i = 1; i < n; i++) {
        if (has_edge(0, i))
            posteriores.push(i);
        else if (has_edge(i, 0))
            anteriores.push(i);
    }
    
    
    
    // Calculamos o caminho até todo monte anterior ao monte 1
    for (int i = 1; i < n; i++) {
        aponta[i] = caminho_anterior(i, anteriores);
        anteriores.pop();
        
        if (aponta[i] > mca)
            mca = aponta[i];
    }
    
    
    
    // Calculamos o caminho até todo monte posterior ao monte 1
    for (int i = 1; i < n; i++) {
        aponta[i] = caminho_posterior(i, posteriores);
        posteriores.pop();
        
        if (apontado[i] > mcp)
            mcp = apontado[i];
    }
    
    
    
    // O maior caminho é dado pelos elementos
    // que apontam (em ordem crescente de caminho)
    // seguido dos elementos
    // apontados (em ordem decrescente de caminho)
    path.resize(n);    
    for (int i = 1; i < mca + mcp; i++) {
        if (aponta[i] != 0)
            path.push_back(aponta[aponta[i]] + 1);
    }
    
        path.push_back(1);
    
    for (int i = 1; i < mcp + mca; i++) {
        if (apontado[i] != 0)
            path.push_back(apontado[apontado[i]] + 1 + mca);
    }
    
    
    
    return path;
}

/* 
    Nao altere nada da main!!!! 
    Para testar seu codigo veja "lib.h"
*/
int main(int argc, char *argv[]) {

    char *filename = NULL;
    if(argc > 1)
        filename = argv[1];

    int n;
    initialize_has_edge(n, filename);

    vector<int> path = solve(n);
    int result = check_path(path, n);
    cout << result << '\n';
    return result;
}
