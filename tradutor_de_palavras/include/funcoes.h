#ifndef FUNCOES_H
# define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "funcoes.h"

#define TAM_MAX_PALAVRA 100
#define TAM_MAX_EMAIL 100
#define TAM_MAX_SENHA 50
#define TAM_MAX_SEQUENCIA 50
#define NUM_TECLAS 10
#define FICHEIRO_USUARIOS "usuarios.txt"
#define FICHEIRO_PALAVRAS "words.txt"

// Estrutura para representar um nó da Trie
typedef struct NoTrie {
    struct NoTrie* filhos[NUM_TECLAS]; // 0-9
    char* palavra;
    bool fimDaPalavra;
} NoTrie;

// Estrutura para representar um usuário
typedef struct Usuario {
    char email[TAM_MAX_EMAIL];
    char senha[TAM_MAX_SENHA];
    struct Usuario* proximo;
} Usuario;

// Estrutura principal do sistema
typedef struct {
    NoTrie* raiz;
    Usuario* usuarios;
} SistemaTradutor;

// Protótipos das funções
NoTrie* createTrieNode();
void insertWord(NoTrie* raiz, const char* palavra);
bool searchWord(NoTrie* raiz, const char* palavra);
void removeWord(NoTrie* raiz, const char* palavra);
void printAllWords(NoTrie* raiz, char* buffer, int depth);
void translateSequence(NoTrie* raiz, const char* sequence);
char* wordToSequence(const char* palavra);
void freeTrieNode(NoTrie* node);
void loadWordsFromFile(NoTrie* raiz, const char* filename);
void saveWordToFile(const char* palavra);
void removeWordFromFile(const char* palavra);
bool authenticateUser(SistemaTradutor* system, const char* email, const char* senha);
bool registerUser(SistemaTradutor* system, const char* email, const char* senha);
void loadUsers(SistemaTradutor* system);
void saveUser(const char* email, const char* senha);
void printWordsForSameSequence(NoTrie* raiz, const char* palavra);
void freeUsers(Usuario* usuarios);
void freeTrieNode(NoTrie* node);
NoTrie* createTrieNode();
void printMenu();
void clearInputBuffer();

#endif
