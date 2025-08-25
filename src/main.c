#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/agenda.h"

void sair() {
    printf("Saindo do programa...\n");
    exit(0);
}
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void wrapperAdicionar() {
    char nome[100], email[100], numero[15];

    printf("\nNome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Numero: ");
    fgets(numero, sizeof(numero), stdin);
    numero[strcspn(numero, "\n")] = 0;

    adicionarContato(nome, email, numero);
}


void wrapperBuscar() {
    char nome[100];
    printf("\nNome para buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    buscarContato(nome);
}

void wrapperRemover() {
    char nome[100];
    printf("\nNome para remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    removerContato(nome);
}

int main() {
    void (*jumptable[6])() = {NULL, wrapperAdicionar, listarContatos, wrapperBuscar, wrapperRemover, sair};

    while (1) {
        printf("\n\n===== MENU DE CONTATOS =====\n");
        printf("1. Adicionar contato\n");
        printf("2. Listar contatos\n");
        printf("3. Buscar contato\n");
        printf("4. Remover contato\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");

        int opcao;
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao < 1 || opcao > 5) {
            printf("Opcao invalida!\n");
            continue;
        }

        jumptable[opcao]();
    }

    return 0;
}
