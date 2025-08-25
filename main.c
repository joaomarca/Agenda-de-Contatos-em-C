#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void adicionarContato(char nome[], char email[], int numero);
void listarContatos();
void buscarContato(char nome[]);
void removerContato(char nome[]);
void sair();

int main() {
    listarContatos();
    return 0;
}


void adicionarContato(char nome[], char email[], int numero) {
    FILE *f = fopen("contatos.txt", "a+");
    if (f == NULL) {
        printf("Erro ao abrir arquivo contatos.txt");
        fclose(f);
        return;
    }

    struct stat file_info;
    stat("contatos.txt", &file_info);

    if (file_info.st_size == 0) {
        fprintf(f, "Nome,Email,Numero\n");
        fprintf(f, "%s,%s,%d", nome, email, numero);
        fclose(f);
        return;
    }

    fprintf(f, "\n%s,%s,%d", nome, email, numero);
    fclose(f);
}

void listarContatos() {
    FILE *f = fopen("contatos.txt", "r");
    if (f == NULL) {
        printf("Erro ao ler arquivo contatos.txt");
        fclose(f);
        return;
    }

    struct stat file_info;
    stat("contatos.txt", &file_info);

    if (file_info.st_size == 0) {
        printf("Agenda de contatos vazia!");
        fclose(f);
        return;
    }

    char buffer[150];

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char *nome = strtok(buffer, ",");
        char *email = strtok(NULL, ",");
        char *numero = strtok(NULL, ",");

        if (nome && email && numero) {
            printf("\nNome: %s\n", nome);
            printf("Email: %s\n", email);
            printf("Numero: %s\n", numero);
        }
    }

    fclose(f);
}