#include <stdio.h>
#include "crud.h"

void create();
void read();
void readById();
void removeById();

int main() {
    int status = 1;

    do {
        printf("\n========== Opcoes ==========\n\n");
        printf(" 1 - Cadastrar aluno:\n");
        printf(" 2 - Listar todos os alunos:\n");
        printf(" 3 - Buscar aluno por matricula:\n");
        printf(" 4 - Remover aluno por matricula:\n");
        printf(" 0 - Sair:\n");
        printf("--> ");
        int option;
        scanf(" %d", &option);

        printf("\n=============================\n");
        switch (option) {
            case 1: create(); break;
            case 2: read(); break;
            case 3: readById(); break;
            case 4: removeById(); break;
            case 0: printf("\nFechando o programa...\n"); status = 0; break;
            default: printf("Opcao invalida!\n"); break;
        } 
        printf("\n=============================\n\n");
    } while (status);

    return 0;
}
