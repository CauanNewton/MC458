#include <iostream>
#include <random>
#include <set>
#include <vector>

/*
 IMPORTANTE:
 Este NAO eh o arquivo lib.h que sera usado no Susy. Eh feito apenas para testes locais.
 Note que para N>1000 este codigo nao funciona devido ao tamanho da matriz 'mat'.
 Caso queira testar instancias grandes localmente, voce deve modificar as funcoes
 "has_edge" e "initialize_has_edge".
*/

int mat[1001][1001];

/* 
    Esta funcao decide se tem tirolesa
    do monte i para o monte j, nesse sentido.
*/
bool has_edge(int i, int j) {
    return mat[i][j];
}

int check_path(std::vector<int> &caminho, int n) {
    // essa funcao checa se seu caminho eh valido, ou seja:
    // 1) os montes sao inteiros de 1 a N
    // 2) nao ha repeticao de montes
    // 3) para todo par de montes adjacentes existe uma tirolesa naquele sentido
    
    // 1)
    for(int i = 0; i < caminho.size(); i++) {
        if(caminho[i] < 1 || caminho[i] > n) {
            std::cout << "ERRO: inteiro " << caminho[i] << " nao esta no intervalo [1," << n << "]\n";
            return 1;
        }
    }
    
    // 2)
    std::set<int> S(caminho.begin(), caminho.end());
    if(S.size() != caminho.size()) {
        std::cout << "ERRO: Repeticao de montes\n";
        return 2;
    }
    
    // 3)
    for(int i = 0; i+1 < caminho.size(); i++) {
        if(!has_edge(caminho[i], caminho[i+1])) {
            std::cout << "ERRO: Nao existe tirolesa de " << caminho[i] << " para " << caminho[i+1] << "\n";
            return 3;
        }
    }

    /*
        O caminho eh valido. Se ele for do tamanho do maior caminho possivel,
        sua resposta sera considerada correta.
    */
    std::cout << "Caminho valido\n";
    std::cout << "Tamanho: " << caminho.size() << "\n";
    for(int i = 0; i < caminho.size(); i++) {
        std::cout << caminho[i];
        if(i == caminho.size() - 1)
            std::cout << "\n";
        else std::cout << " ";
    }

    return 0;
}

void initialize_has_edge(int &n, char *filename) {

    /* 
        Voce pode alterar como a direcao das tirolesas 
        eh escolhida a fim de testar seu programa.
        OBS: Essa NAO eh funcao que sera usada no Susy.
        O modo como as direcoes sao escolhidas nao eh dada para 
        voce e voce NAO deve assumir nada sobre as direcoes
    */

    /* 
        Exemplo do enunciado. Voce pode modificar G
        a vontede para testar uma entrada especifica
    */
    n = 4;
    int G[4][4] = {
        {0, 0, 0, 1},
        {1, 0, 1, 1},
        {1, 0, 0, 1},
        {0, 0, 0, 0}
    };

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            mat[i+1][j+1] = G[i][j];

    /* Direcao aleatoria */
    /*
    n = 1000;
    std::mt19937_64 rng(n); // gerador aleatorio
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            if(rng() % 2) { 
                // tirolesa de i para j
                mat[i][j] = 1;
            } else {
                // tirolesa de j para i
                mat[j][i] = 1;
            }
        }
    }
    */
}
