#include "funcoes.h"

// Função recursiva para imprimir palavras e digitos
void printAllWordsHelper(NoTrie* raiz, char* buffer, int depth) {
    if (!raiz) return;
    
    if (raiz->fimDaPalavra && raiz->palavra) {
        char* sequence = wordToSequence(raiz->palavra);
        if (sequence) {
            printf("%-15s → %s\n", raiz->palavra, sequence);
            free(sequence);
        } else {
            printf("%-15s → [erro na conversão]\n", raiz->palavra);
        }
    }
    
    for (int i = 0; i < NUM_TECLAS; i++) {
        if (raiz->filhos[i] != NULL) {
            buffer[depth] = '0' + i;
            buffer[depth + 1] = '\0';
            printAllWordsHelper(raiz->filhos[i], buffer, depth + 1);
        }
    }
}

void printAllWords(NoTrie* raiz, char* buffer, int depth) {
    printf("\n=== TODAS AS PALAVRAS E SEUS CÓDIGOS ===\n");
    printf("%-15s   %s\n", "PALAVRA", "CÓDIGO");
    printf("%-15s   %s\n", "-------", "------");
    printAllWordsHelper(raiz, buffer, depth);
    printf("========================================\n\n");
}
