#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../include/agenda.h"

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

void adicionarContato(char nome[], char email[], char numero[]) {
    FILE *f = fopen("contatos.txt", "a+");
    if (f == NULL) {
        printf("Erro ao abrir arquivo contatos.txt\n");
        fclose(f);
        return;
    }

    struct stat file_info;
    stat("contatos.txt", &file_info);

    if (file_info.st_size == 0) {
        remove("contatos.txt");
        f = fopen("contatos.txt", "w");
        fprintf(f, "Nome,Email,Numero\n");
        fprintf(f, "%s,%s,%s", nome, email, numero);
        fclose(f);
        return;
    }

    fprintf(f, "\n%s,%s,%s", nome, email, numero);
    printf("\nContato adicionado!\n");
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
    int encontrado = 0;

    printf("\nListando contatos..\n\n");

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            continue;
        }
        if (strcmp(buffer, "Nome,Email,Numero") == 0) {
            continue;
        }

        char *nome = strtok(buffer, ",");
        char *email = strtok(NULL, ",");
        char *numero = strtok(NULL, ",");

        if (nome && email && numero) {
            encontrado = 1;
            printf("\nNome: %s\n", nome);
            printf("Email: %s\n", email);
            printf("Numero: %s\n", numero);
        }
    }

    if (!encontrado) {
        printf("Nenhum contato encontrado!");
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

    printf("Buscando contato..\n\n");

    char buffer[150];
    char nomeSanitizado[100];
    char procuradoSanitizado[100];
    int encontrado = 0;

    normalizarString(procuradoSanitizado, nomeProcurado);

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            continue;
        }
        if (strcmp(buffer, "Nome,Email,Numero") == 0) {
            continue;
        }

        char analise[150];
        strcpy(analise, buffer);
        char *nome = strtok(analise, ",");

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

    printf("\nRemovendo contato..\n\n");

    char buffer[150];
    char nomeSanitizado[100];
    char procuradoSanitizado[100];
    int encontrado = 0;

    normalizarString(procuradoSanitizado, nomeProcurado);

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0) {
            continue;
        }
        if (strcmp(buffer, "Nome,Email,Numero") == 0) {
            continue;
        }

        char linha[150];
        char analise[150];
        strcpy(linha, buffer);
        strcpy(analise, buffer);

        char *nome = strtok(analise, ",");

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