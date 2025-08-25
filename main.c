#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>

void normalizarString(char *dest, const char *src);
void adicionarContato(char nome[], char email[], int numero);
void listarContatos();
void buscarContato(char nomeProcurado[]);
void removerContato(char nomeProcurado[]);
void sair();

int main() {
    return 0;
}


void normalizarString(char *dest, const char *src) {
    while (*src) {
        if (!isspace((unsigned char)*src)) {
            *dest = tolower((unsigned char)*src);
            dest++;
        }
        src++;
    }
    *dest = '\0';
}

void adicionarContato(char nome[], char email[], int numero) {
    FILE *f = fopen("contatos.txt", "a+");
    if (f == NULL) {
        printf("Erro ao abrir arquivo contatos.txt\n");
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
        printf("Erro ao ler arquivo contatos.txt\n");
        fclose(f);
        return;
    }

    struct stat file_info;
    stat("contatos.txt", &file_info);

    if (file_info.st_size == 0) {
        printf("Agenda de contatos vazia!\n");
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

void buscarContato(char nomeProcurado[]) {
    FILE *f = fopen("contatos.txt", "r");
    if (f == NULL) {
        printf("Erro ao ler arquivo contatos.txt\n");
        fclose(f);
        return;
    }

    struct stat file_info;
    stat("contatos.txt", &file_info);

    if (file_info.st_size == 0) {
        printf("Agenda de contatos vazia!\n");
        fclose(f);
        return;
    }

    char buffer[150];
    char nomeSanitizado[100];
    char procuradoSanitizado[100];
    int encontrado = 0;

    normalizarString(procuradoSanitizado, nomeProcurado);

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char *nome = strtok(buffer, ",");

        if (nome) {
            normalizarString(nomeSanitizado, nome);

            if (strcmp(nomeSanitizado, procuradoSanitizado) == 0) {
                encontrado = 1;
                char *email = strtok(NULL, ",");
                char *numero = strtok(NULL, ",");

                printf("\nNome: %s\n", nome);
                printf("Email: %s\n", email);
                printf("Numero: %s\n", numero);
            }
        }
    }

    if (!encontrado) {
        printf("\nContato não encontrado!\n");
    }
    fclose(f);
}

void removerContato(char nomeProcurado[]) {
    FILE *f = fopen("contatos.txt", "r");
    if (f == NULL) {
        printf("Erro ao ler arquivo contatos.txt\n");
        fclose(f);
        return;
    }

    struct stat file_info;
    stat("contatos.txt", &file_info);

    if (file_info.st_size == 0) {
        printf("Agenda de contatos vazia!\n");
        fclose(f);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(f);
        return;
    }

    char buffer[150];
    char nomeSanitizado[100];
    char procuradoSanitizado[100];
    int encontrado = 0;

    normalizarString(procuradoSanitizado, nomeProcurado);

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char linha[150];
        strcpy(linha, buffer);

        char *nome = strtok(buffer, ",");

        if (nome) {
            normalizarString(nomeSanitizado, nome);

            if (strcmp(nomeSanitizado, procuradoSanitizado) == 0) {
                encontrado++;
                continue;
            }
        }

        fprintf(temp, "%s\n", linha);
    }

    fclose(f);
    fclose(temp);

    remove("contatos.txt");
    rename("temp.txt", "contatos.txt");

    if (!encontrado) {
        printf("\nContato não encontrado!\n");
        return;
    } else if (encontrado == 1) {
        printf("Contato deletado com sucesso!\n");
    } else {
        printf("%d contatos deletados com sucesso!", encontrado);
    }
}