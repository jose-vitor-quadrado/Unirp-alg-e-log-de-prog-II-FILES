#include <stdio.h>
#include <string.h>

const char *DATA = "data.dat";

typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;

void create() {
    Student student;

    FILE *fp = fopen(DATA, "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\n");
    
    printf("Digite a matricula: ");
    scanf(" %d", &student.id);

    getchar();
    printf("Digite o nome do aluno: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Digite a nota do aluno: ");
    scanf(" %f", &student.gpa);

    fwrite(&student, sizeof(Student), 1, fp);
    fclose(fp);

    printf("\nAluno cadastrado com sucesso!\n");
}

void read() {
    Student student;
    int count = 0;

    FILE *fp = fopen(DATA, "rb");
    if (!fp) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\n====== Lista de alunos ======\n\n");
    while (fread(&student, sizeof(Student), 1, fp) == 1) {
        printf(" Matricula: %d\n", student.id);
        printf(" Nome: %s\n", student.name);
        printf(" Nota: %.2f\n", student.gpa);
        count++;
    }

    if (count == 0) {
        printf("Nenhum aluno encontrado.\n");
    }

    fclose(fp);
}

void readById() {
    Student student;
    int id, found = 0;

    FILE *fp = fopen(DATA, "rb");
    if (!fp) {
        printf("Arquivo inexistente.\n");
        return;
    }

    printf("\nDigite a matricula a buscar: ");
    scanf(" %d", &id);

    while (fread(&student, sizeof(Student), 1, fp) == 1) {
        if (student.id == id) {
            printf("\nAluno encontrado:\n");
            printf(" Matricula: %d\n", student.id);
            printf(" Nome: %s\n", student.name);
            printf(" Nota: %.2f\n", student.gpa);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nAluno nao encontrado!\n");
    }

    fclose(fp);
}

void removeById() {
    Student student;
    int id, removed = 0;

    FILE *fp = fopen(DATA, "rb");
    if (!fp) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    FILE *tmp = fopen("tmp.dat", "wb");
    if (!tmp) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(fp);
        return;
    }

    printf("\nDigite a matricula do aluno a ser removido: ");
    scanf(" %d", &id);

    while (fread(&student, sizeof(Student), 1, fp) == 1) {
        if (student.id != id) {
            fwrite(&student, sizeof(Student), 1, tmp);
        }
        else {
            removed = 1;
        }
    }

    fclose(fp);
    fclose(tmp);

    if (remove(DATA) != 0) {
        printf("Erro ao remover o arquivo antigo.\n");
        return;
    }

    if (rename("tmp.dat", DATA) != 0) {
        printf("Erro ao renomear o arquivo temporario!\n");
        return;
    }

    if (removed) {
        printf("Aluno removido com sucesso!\n");
    }
    else {
        printf("Aluno nao encontrado!\n");
    }
}