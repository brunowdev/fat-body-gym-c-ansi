#include <stdio.h>
#include <stdlib.h>

#include "IndexAlunoCodigo.h"

IndexAlunoCodigo * criarListaIndexCodigo()
{
    return NULL;
}

IndexAlunoCodigo * criarNoIndexCodigo(int codigo, int posicao)
{
    IndexAlunoCodigo* no = (IndexAlunoCodigo*) malloc(sizeof(IndexAlunoCodigo));
    no->codigo = codigo;
    no->posicao = posicao;
    no->proximo = NULL;
    return no;
}

IndexAlunoCodigo* adicionarIndexCodigo(IndexAlunoCodigo *lista, int codigo, int posicao)
{

    IndexAlunoCodigo * no = criarNoIndexCodigo(codigo, posicao);
    if (isListaVaziaIndexAlunoCodigo(lista))
    {
        return no;
    }
    if (lista->codigo > codigo)
    {
        no->proximo = lista;
        return no;
    }
    IndexAlunoCodigo *proximo = lista;
    while (proximo != NULL && proximo->proximo != NULL && proximo->proximo->codigo < codigo)
    {
        proximo = proximo->proximo;
    }
    no->proximo = proximo->proximo;
    proximo->proximo = no;
    return lista;
}

IndexAlunoCodigo* buscarIndexCodigo(IndexAlunoCodigo *lista, int codigo)
{
    if (isListaVaziaIndexAlunoCodigo(lista))
    {
        return NULL;
    }
    IndexAlunoCodigo* proximo = lista;
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

IndexAlunoCodigo* removerIndexCodigo(IndexAlunoCodigo* lista, int codigo)
{
    if (isListaVaziaIndexAlunoCodigo(lista))
    {
        return lista;
    }
    IndexAlunoCodigo *no = lista, *proximo = lista;
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
        IndexAlunoCodigo* temp = proximo;
        no->proximo = proximo->proximo;
        free(temp);
    }
    return lista;
}

IndexAlunoCodigo* limparListaIndexCodigo(IndexAlunoCodigo* lista)
{
    if (!isListaVaziaIndexAlunoCodigo(lista))
    {
        lista->proximo = limparListaIndexCodigo(lista->proximo);
        free(lista);
    }
    return NULL;
}

int isListaVaziaIndexAlunoCodigo(IndexAlunoCodigo* lista)
{
    if (lista == NULL)
    {
        return 1;
    }
    return 0;
}

int tamanhoListaIndexAlunoCodigo(IndexAlunoCodigo* lista)
{
    if (isListaVaziaIndexAlunoCodigo(lista) == 1)
    {
        return 0;
    }
    IndexAlunoCodigo* tmp = lista;
    int tamanhoLista = 0;
    while (tmp != NULL)
    {
        tmp = tmp->proximo;
        tamanhoLista++;
    }
    return tamanhoLista;
}

