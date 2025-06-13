#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "funcoes.h"

void translateSequence(NoTrie* raiz, const char* sequence) {
    if (!raiz || !sequence) return;
    
    NoTrie* current = raiz;
    bool endsWithZero = (sequence[strlen(sequence) - 1] == '0');
    
    // Navegar até o nó correspondente
    for (int i = 0; sequence[i] != '\0'; i++) {
        int index = sequence[i] - '0';
        if (current->filhos[index] == NULL) {
            printf("Erro: Sequência '%s' não encontrada.\n", sequence);
            return;
        }
        current = current->filhos[index];
    }
    
    printf("\n=== TRADUÇÃO DA SEQUÊNCIA '%s' ===\n", sequence);
    
    if (endsWithZero) {
        // Imprimir todas as palavras da sequência
        bool found = false;
        if (current->fimDaPalavra && current->palavra) {
            printf("- %s\n", current->palavra);
            found = true;
        }
        
        NoTrie* alt = current->filhos[0];
        while (alt != NULL) {
            if (alt->fimDaPalavra && alt->palavra) {
                printf("- %s\n", alt->palavra);
                found = true;
            }
            alt = alt->filhos[0];
        }
        
        if (!found) {
            printf("Nenhuma palavra encontrada para esta sequência.\n");
        }
    } else {
        // Imprimir apenas a primeira palavra
        if (current->fimDaPalavra && current->palavra) {
            printf("Palavra: %s\n", current->palavra);
        } else {
            printf("Nenhuma palavra encontrada para esta sequência.\n");
        }
    }
    printf("=====================================\n\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMenu() {
    printf("\n=== TRADUTOR DUMBPHONE ===\n");
    printf("1. Inserir nova palavra\n");
    printf("2. Procurar palavra\n");
    printf("3. Remover palavra\n");
    printf("4. Imprimir todas as palavras\n");
    printf("5. Traduzir sequência numérica\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    SistemaTradutor system;
    system.raiz = createTrieNode();
    system.usuarios = NULL;
    
    printf("=== SISTEMA TRADUTOR DUMBPHONE ===\n");
    printf("Mapeamento de teclas:\n");
    printf("2: ABC, 3: DEF, 4: GHI, 5: JKL\n");
    printf("6: MNO, 7: PQRS, 8: TUV, 9: WXYZ\n");
    printf("0: Alternativa (para múltiplas palavras)\n\n");
    
    // Carregar usuários
    loadUsers(&system);
    
    // Autenticação
    char email[TAM_MAX_EMAIL], senha[TAM_MAX_SENHA];
    int authChoice;
    bool authenticated = false;
    
    while (!authenticated) {
        printf("1. Login\n2. Registrar\nEscolha: ");
        scanf("%d", &authChoice);
        clearInputBuffer();
        
        printf("Email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';
        
        printf("Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';
        
        if (authChoice == 1) {
            if (authenticateUser(&system, email, senha)) {
                printf("Sucesso: Login realizado!\n");
                authenticated = true;
            } else {
                printf("Erro: Credenciais inválidas.\n");
            }
        } else if (authChoice == 2) {
            if (registerUser(&system, email, senha)) {
                printf("Sucesso: Usuário registrado!\n");
                authenticated = true;
            } else {
                printf("Erro: Usuário já existe.\n");
            }
        }
    }
    
    // Carregar palavras
    loadWordsFromFile(system.raiz, FICHEIRO_PALAVRAS);
    
    // Menu principal
    int choice;
    char palavra[TAM_MAX_PALAVRA];
    char sequence[TAM_MAX_SEQUENCIA];
    char buffer[TAM_MAX_SEQUENCIA];
    
    do {
        printMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                printf("Digite a palavra para inserir: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';
                
                if (searchWord(system.raiz, palavra)) {
                    char* sequence = wordToSequence(palavra);
                    if (sequence) {
                        printf("Aviso: Palavra '%s' já existe com código '%s'.\n", palavra, sequence);
                        free(sequence);
                    } else {
                        printf("Aviso: Palavra '%s' já existe.\n", palavra);
                    }
                } else {
                    insertWord(system.raiz, palavra);
                    saveWordToFile(palavra);
                }
                break;
                
            case 2:
                printf("Digite a palavra para procurar: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';
                
                if (searchWord(system.raiz, palavra)) {
                    char* sequence = wordToSequence(palavra);
                    if (sequence) {
                        printf("Sucesso: Palavra '%s' encontrada com código '%s'.\n", palavra, sequence);
                        free(sequence);
                    } else {
                        printf("Sucesso: Palavra '%s' encontrada.\n", palavra);
                    }
                } else {
                    printf("Erro: Palavra '%s' não encontrada.\n", palavra);
                }
                break;
                
            case 3:
                printf("Digite a palavra para remover: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';
                removeWord(system.raiz, palavra);
                break;
                
            case 4:
                printAllWords(system.raiz, buffer, 0);
                break;
                
            case 5:
                printf("Digite a sequência numérica (termine com 0 para ver todas as alternativas): ");
                fgets(sequence, sizeof(sequence), stdin);
                sequence[strcspn(sequence, "\n")] = '\0';
                translateSequence(system.raiz, sequence);
                break;
                
            case 6:
                printf("Encerrando o programa...\n");
                break;
                
            default:
                printf("Erro: Opção inválida.\n");
                break;
        }
    } while (choice != 6);
    
    // Limpeza de memória
    freeTrieNode(system.raiz);
    freeUsers(system.usuarios);
    
    return 0;
}
