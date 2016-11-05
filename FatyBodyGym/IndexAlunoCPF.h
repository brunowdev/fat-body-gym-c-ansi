#ifndef INDEXALUNOCPF_H_INCLUDED
#define INDEXALUNOCPF_H_INCLUDED

#include <stdio.h>

struct indexAlunoCPF
{
    char cpf[15];
    int posicao;
    struct indexAlunoCPF * proximo;
};

typedef struct indexAlunoCPF IndexAlunoCPF;

IndexAlunoCPF* criarListaIndexCPF();
IndexAlunoCPF* adicionarIndexCPF(IndexAlunoCPF * lista, char cpf[15], int posicao);
IndexAlunoCPF* buscarIndexCPF(IndexAlunoCPF * lista, char cpf[15]);
IndexAlunoCPF* removerIndexCPF(IndexAlunoCPF* lista, char cpf[15]);
IndexAlunoCPF* limparListaIndexCPF(IndexAlunoCPF * lista);
int isListaVaziaIndexCPF(IndexAlunoCPF * lista);

#endif // INDEXALUNOCPF_H_INCLUDED
