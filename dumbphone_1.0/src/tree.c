#include "funcoes.h"

NoTrie* createTrieNode() {
    NoTrie* node = (NoTrie*)malloc(sizeof(NoTrie));
    if (!node) {
        printf("Erro: Falha na alocação de memória!\n");
        exit(1);
    }
    
    for (int i = 0; i < NUM_TECLAS; i++) {
        node->filhos[i] = NULL;
    }
    node->palavra = NULL;
    node->fimDaPalavra = false;
    return node;
}

void freeTrieNode(NoTrie* node) {
    if (!node) return;
    
    for (int i = 0; i < NUM_TECLAS; i++) {
        freeTrieNode(node->filhos[i]);
    }
    
    if (node->palavra) {
        free(node->palavra);
    }
    free(node);
}
