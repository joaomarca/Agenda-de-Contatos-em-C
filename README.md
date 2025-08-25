# 📒 Agenda de Contatos em C

Sistema de gerenciamento de contatos em C, com armazenamento em arquivo de texto e compilação via CMake.

## 📝 Funcionalidades
- Adicionar contato (nome, e-mail, telefone)
- Listar contatos
- Buscar contato pelo nome (ignora maiúsculas/minúsculas e espaços)
- Remover contato do arquivo
- Menu interativo com jump table

## 📁 Estrutura do Projeto
```
/Agenda-de-Contatos-em-C
│
├── /src
│   └── agenda.h
│   └── main.c
├── /include
│   └── agenda.h
├── CMakeLists.txt
├── contatos.txt (criado automaticamente)
```

## 🚀 Como Executar
1. Clone este repositório: `git clone https://github.com/joaomarca/Agenda-de-Contatos-em-C`
2. cd Agenda-de-Contatos-em-C && mkdir build && cd build
3. cmake ..
4. make
5. ./main

## 📝 Observações
- O arquivo contatos.txt salva os dados de forma persistente.
- A busca ignora maiúsculas/minúsculas e espaços, mantendo acentos.
- A remoção de contatos não deixa linhas em branco no arquivo.
- Ao criar o arquivo pela primeira vez, a função adicionarContato() gera a linha de cabeçalho "Nome,Email,Numero", que é ignorada automaticamente pelas funções de listagem, busca e remoção.


