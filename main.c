#include <stdio.h>
#include <sys/stat.h>

void adicionarContato(char nome[], char email[], int numero);
void listarContatos();
void buscarContato(char nome[]);
void removerContato(char nome[]);
void sair();

int main() {
    adicionarContato("Nome", "Email", 0);
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
        fprintf(f, "%s,%s,%d", nome, email, numero);
        fclose(f);
        return;
    }

    fprintf(f, "\n%s,%s,%d", nome, email, numero);
    fclose(f);
}