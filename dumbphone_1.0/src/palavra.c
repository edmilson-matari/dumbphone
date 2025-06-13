#include "funcoes.h"

// Mapeamento de teclas para letras
char mapaTeclas[10][5] = {
    "",      // 0
    "",      // 1
    "abc",   // 2
    "def",   // 3
    "ghi",   // 4
    "jkl",   // 5
    "mno",   // 6
    "pqrs",  // 7
    "tuv",   // 8
    "wxyz"   // 9
};

//Converte a palavra na sua sequência numérica
char* wordToSequence(const char* palavra) {
    char* sequence = (char*)malloc(TAM_MAX_SEQUENCIA);
    if (!sequence) return NULL;
    
    int seqIndex = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        char c = tolower(palavra[i]);
        bool found = false;
        
        for (int key = 2; key <= 9; key++) {
            for (int j = 0; mapaTeclas[key][j] != '\0'; j++) {
                if (mapaTeclas[key][j] == c) {
                    sequence[seqIndex++] = '0' + key;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        
        if (!found && c != ' ') {
            free(sequence);
            return NULL;
        }
    }
    sequence[seqIndex] = '\0';
    return sequence;
}

void insertWord(NoTrie* raiz, const char* palavra) {
    if (!raiz || !palavra) return;
    
    char* sequence = wordToSequence(palavra);
    if (!sequence) {
        printf("Erro: Não foi possível converter a palavra '%s' para sequência numérica.\n", palavra);
        return;
    }
    
    NoTrie* current = raiz;
    
    for (int i = 0; sequence[i] != '\0'; i++) {
        int index = sequence[i] - '0';
        if (current->filhos[index] == NULL) {
            current->filhos[index] = createTrieNode();
        }
        current = current->filhos[index];
    }
    
    // Se já existe uma palavra neste nó, criar alternativa com 0
    if (current->fimDaPalavra && current->palavra != NULL) {
        if (current->filhos[0] == NULL) {
            current->filhos[0] = createTrieNode();
        }
        current = current->filhos[0];
    }
    
    current->fimDaPalavra = true;
    if (current->palavra) {
        free(current->palavra);
    }
    current->palavra = (char*)malloc(strlen(palavra) + 1);
    strcpy(current->palavra, palavra);
    
    printf("Sucesso: Palavra '%s' inserida com código '%s'.\n", palavra, sequence);
    free(sequence);
}

bool searchWord(NoTrie* raiz, const char* palavra) {
    if (!raiz || !palavra) return false;
    
    char* sequence = wordToSequence(palavra);
    if (!sequence) return false;
    
    NoTrie* current = raiz;
    
    for (int i = 0; sequence[i] != '\0'; i++) {
        int index = sequence[i] - '0';
        if (current->filhos[index] == NULL) {
            free(sequence);
            return false;
        }
        current = current->filhos[index];
    }
    
    free(sequence);
    
    // Verificar se a palavra existe neste nó ou em alternativas
    if (current->fimDaPalavra && current->palavra && strcmp(current->palavra, palavra) == 0) {
        return true;
    }
    
    // Verificar alternativas (nós com 0)
    current = current->filhos[0];
    while (current != NULL) {
        if (current->fimDaPalavra && current->palavra && strcmp(current->palavra, palavra) == 0) {
            return true;
        }
        current = current->filhos[0];
    }
    
    return false;
}

void removeWord(NoTrie* raiz, const char* palavra) {
    if (!searchWord(raiz, palavra)) {
        printf("Erro: Palavra '%s' não encontrada.\n", palavra);
        return;
    }
    
    char* sequence = wordToSequence(palavra);
    if (!sequence) return;
    
    NoTrie* current = raiz;
    
    for (int i = 0; sequence[i] != '\0'; i++) {
        int index = sequence[i] - '0';
        current = current->filhos[index];
    }
    
    // Remover a palavra específica
    if (current->fimDaPalavra && current->palavra && strcmp(current->palavra, palavra) == 0) {
        free(current->palavra);
        current->palavra = NULL;
        current->fimDaPalavra = false;
    } else {
        // Procurar nas alternativas
        NoTrie* prev = current;
        current = current->filhos[0];
        while (current != NULL) {
            if (current->fimDaPalavra && current->palavra && strcmp(current->palavra, palavra) == 0) {
                free(current->palavra);
                current->palavra = NULL;
                current->fimDaPalavra = false;
                break;
            }
            prev = current;
            current = current->filhos[0];
        }
    }
    
    free(sequence);
    removeWordFromFile(palavra);
    printf("Sucesso: Palavra '%s' removida.\n", palavra);
}
