#include <stdio.h>
#include <stdlib.h>

#include "IndexTreinoAluno.h"

IndexTreinoAluno * criarListaIndexTreinoAluno()
{
    return NULL;
}

IndexTreinoAluno * criarNoIndexTreinoAluno(int codigo, int posicao)
{
    IndexTreinoAluno* no = (IndexTreinoAluno*) malloc(sizeof(IndexTreinoAluno));
    no->codigo = codigo;
    no->posicao = posicao;
    no->proximo = NULL;
    return no;
}

IndexTreinoAluno* adicionarIndexTreinoAluno(IndexTreinoAluno *lista, int codigo, int posicao)
{

    IndexTreinoAluno * no = criarNoIndexTreinoAluno(codigo, posicao);
    if (isListaVaziaIndexTreinoAluno(lista))
    {
        return no;
    }
    if (lista->codigo > codigo)
    {
        no->proximo = lista;
        return no;
    }
    IndexTreinoAluno *proximo = lista;
    while (proximo != NULL && proximo->proximo != NULL && proximo->proximo->codigo < codigo)
    {
        proximo = proximo->proximo;
    }
    no->proximo = proximo->proximo;
    proximo->proximo = no;
    return lista;
}

IndexTreinoAluno* buscarIndexTreinoAluno(IndexTreinoAluno *lista, int codigo)
{
    if (isListaVaziaIndexTreinoAluno(lista))
    {
        return NULL;
    }
    IndexTreinoAluno* proximo = lista;
    while (proximo != NULL)
    {
        if (proximo->codigo == codigo)
        {
            return proximo;
        }
        proximo = proximo->proximo;
    }
    return NULL;
}

IndexTreinoAluno* removerIndexTreinoAluno(IndexTreinoAluno* lista, int codigo)
{
    if (isListaVaziaIndexTreinoAluno(lista))
    {
        return lista;
    }
    IndexTreinoAluno *no = lista, *proximo = lista;
    if (lista->codigo == codigo)
    {
        proximo = lista->proximo;
        free(lista);
        return proximo;
    }
    while (proximo != NULL && proximo->codigo != codigo)
    {
        no = proximo;
        proximo = no->proximo;
    }
    if (proximo != NULL && proximo->codigo == codigo)
    {
        IndexTreinoAluno* temp = proximo;
        no->proximo = proximo->proximo;
        free(temp);
    }
    return lista;
}

IndexTreinoAluno* limparListaIndexTreinoAluno(IndexTreinoAluno* lista)
{
    if (!isListaVaziaIndexTreinoAluno(lista))
    {
        lista->proximo = limparListaIndexTreinoAluno(lista->proximo);
        free(lista);
    }
    return NULL;
}

int isListaVaziaIndexTreinoAluno(IndexTreinoAluno* lista)
{
    if (lista == NULL)
    {
        return 1;
    }
    return 0;
}

int tamanhoListaIndexTreinoAluno(IndexTreinoAluno* lista)
{
    if (isListaVaziaIndexTreinoAluno(lista) == 1)
    {
        return 0;
    }
    IndexTreinoAluno* tmp = lista;
    int tamanhoLista = 0;
    while (tmp != NULL)
    {
        tmp = tmp->proximo;
        tamanhoLista++;
    }
    return tamanhoLista;
}


