#include "funcoes.h"

void loadUsers(SistemaTradutor* system) {
    FILE* file = fopen(FICHEIRO_USUARIOS, "r");
    if (!file) {
        printf("Aviso: Arquivo de usuários não encontrado. Será criado ao registrar usuários.\n");
        return;
    }
    
    char email[TAM_MAX_EMAIL], senha[TAM_MAX_SENHA];
    while (fscanf(file, "%s %s", email, senha) == 2) {
        Usuario* newUser = (Usuario*)malloc(sizeof(Usuario));
        strcpy(newUser->email, email);
        strcpy(newUser->senha, senha);
        newUser->proximo = system->usuarios;
        system->usuarios = newUser;
    }
    
    fclose(file);
}

void saveUser(const char* email, const char* senha) {
    FILE* file = fopen(FICHEIRO_USUARIOS, "a");
    if (file) {
        fprintf(file, "%s %s\n", email, senha);
        fclose(file);
    }
}

bool authenticateUser(SistemaTradutor* system, const char* email, const char* senha) {
    Usuario* current = system->usuarios;
    while (current) {
        if (strcmp(current->email, email) == 0 && strcmp(current->senha, senha) == 0) {
            return true;
        }
        current = current->proximo;
    }
    return false;
}

bool registerUser(SistemaTradutor* system, const char* email, const char* senha) {
    // Verificar se usuário já existe
    Usuario* current = system->usuarios;
    while (current) {
        if (strcmp(current->email, email) == 0) {
            return false;
        }
        current = current->proximo;
    }
    
    // Adicionar novo usuário
    Usuario* newUser = (Usuario*)malloc(sizeof(Usuario));
    strcpy(newUser->email, email);
    strcpy(newUser->senha, senha);
    newUser->proximo = system->usuarios;
    system->usuarios = newUser;
    
    saveUser(email, senha);
    return true;
}

void freeUsers(Usuario* usuarios) {
    while (usuarios) {
        Usuario* temp = usuarios;
        usuarios = usuarios->proximo;
        free(temp);
    }
}
