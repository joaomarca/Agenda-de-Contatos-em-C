#ifndef AGENDA_H
#define AGENDA_H

void normalizarString(char *dest, const char *src);
void adicionarContato(char nome[], char email[], char numero[]);
void listarContatos();
void buscarContato(char nomeProcurado[]);
void removerContato(char nomeProcurado[]);

#endif
