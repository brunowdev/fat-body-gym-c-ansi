#include <stdio.h>
#include <stdlib.h>

#include "IndexAlunoCPF.h"

IndexAlunoCPF * criarListaIndexCPF()
{
    return NULL;
}

IndexAlunoCPF* criarNoIndexCPF(char cpf[15], int posicao)
{
    IndexAlunoCPF* no = (IndexAlunoCPF*) malloc(sizeof(IndexAlunoCPF));
    strcpy(no->cpf, cpf);
    no->posicao = posicao;
    no->proximo = NULL;
    return no;
}

IndexAlunoCPF* adicionarIndexCPF(IndexAlunoCPF *lista, char cpf[15], int posicao)
{

    IndexAlunoCPF * no = criarNoIndexCPF(cpf, posicao);
    if (isListaVaziaIndexCPF(lista))
    {
        return no;
    }
    if (strcmp(lista->cpf, cpf) < 0)
    {
        no->proximo = lista;
        return no;
    }
    IndexAlunoCPF *proximo = lista;
    while (proximo != NULL && proximo->proximo != NULL && strcmp(proximo->proximo->cpf, cpf) < 0)
    {
        proximo = proximo->proximo;
    }
    no->proximo = proximo->proximo;
    proximo->proximo = no;
    return lista;
}

IndexAlunoCPF* buscarIndexCPF(IndexAlunoCPF *lista, char cpf[15])
{
    if (isListaVaziaIndexCPF(lista))
    {
        return NULL;
    }
    IndexAlunoCPF* proximo = lista;
    while (proximo != NULL)
    {
        if (strcmp(proximo->cpf, cpf) == 0)
        {
            return proximo;
        }
        proximo = proximo->proximo;
    }
    return NULL;
}

IndexAlunoCPF* removerIndexCPF(IndexAlunoCPF* lista, char cpf[15])
{
    if (isListaVaziaIndexCPF(lista))
    {
        return lista;
    }
    IndexAlunoCPF *no = lista, *proximo = lista;
    if (strcmp(lista->cpf, cpf) == 0)
    {
        proximo = lista->proximo;
        free(lista);
        return proximo;
    }
    while (proximo != NULL && strcmp(proximo->cpf, cpf) != 0)
    {
        no = proximo;
        proximo = no->proximo;
    }
    if (proximo != NULL && strcmp(proximo->cpf, cpf) == 0)
    {
        IndexAlunoCPF * temp = proximo;
        no->proximo = proximo->proximo;
        free(temp);
    }
    return lista;
}

IndexAlunoCPF* limparListaIndexCPF(IndexAlunoCPF* lista)
{
    if (!isListaVaziaIndexCPF(lista))
    {
        lista->proximo = limparListaIndexCPF(lista->proximo);
        free(lista);
    }
    return NULL;
}

int isListaVaziaIndexCPF(IndexAlunoCPF* lista)
{
    if (lista == NULL)
    {
        return 1;
    }
    return 0;
}

int tamanhoListaIndexCPF(IndexAlunoCPF* lista)
{
    if (isListaVaziaIndexCPF(lista) == 1)
    {
        return 0;
    }
    IndexAlunoCPF* tmp = lista;
    int tamanhoLista = 0;
    while (tmp != NULL)
    {
        tmp = tmp->proximo;
        tamanhoLista++;
    }
    return tamanhoLista;
}

