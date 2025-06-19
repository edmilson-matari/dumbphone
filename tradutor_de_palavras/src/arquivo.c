#include "funcoes.h"

void loadWordsFromFile(NoTrie* raiz, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Aviso: Arquivo de palavras não encontrado. Será criado ao adicionar palavras.\n");
        return;
    }
    
    char palavra[TAM_MAX_PALAVRA];
    int count = 0;
    
    while (fgets(palavra, sizeof(palavra), file)) {
        // Remover quebra de linha
        palavra[strcspn(palavra, "\n")] = '\0';
        if (strlen(palavra) > 0) {
            insertWord(raiz, palavra);
            count++;
        }
    }
    
    fclose(file);
    printf("Sucesso: %d palavras carregadas do arquivo.\n", count);
}

void saveWordToFile(const char* palavra) {
    FILE* file = fopen(FICHEIRO_PALAVRAS, "a");
    if (file) {
        fprintf(file, "%s\n", palavra);
        fclose(file);
    }
}

void removeWordFromFile(const char* palavra) {
    FILE* file = fopen(FICHEIRO_PALAVRAS, "r");
    if (!file) return;
    
    FILE* temp = fopen("temp_words.txt", "w");
    if (!temp) {
        fclose(file);
        return;
    }
    
    char line[TAM_MAX_PALAVRA];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, palavra) != 0) {
            fprintf(temp, "%s\n", line);
        }
    }
    
    fclose(file);
    fclose(temp);
    remove(FICHEIRO_PALAVRAS);
    rename("temp_words.txt", FICHEIRO_PALAVRAS);
}
