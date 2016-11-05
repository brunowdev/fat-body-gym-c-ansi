#include <stdio.h>
#include <stdlib.h>

#include "IndexExercicioCodigo.h"

IndexExercicioCodigo * criarListaIndexCodigoExercicio()
{
    return NULL;
}

IndexExercicioCodigo * criarNoIndexCodigoExercicio(int codigo, int posicao)
{
    IndexExercicioCodigo* no = (IndexExercicioCodigo*) malloc(sizeof(IndexExercicioCodigo));
    no->codigo = codigo;
    no->posicao = posicao;
    no->proximo = NULL;
    return no;
}

IndexExercicioCodigo* adicionarIndexCodigoExercicio(IndexExercicioCodigo *lista, int codigo, int posicao)
{

    IndexExercicioCodigo * no = criarNoIndexCodigoExercicio(codigo, posicao);
    if (isListaVaziaIndexExercicioCodigo(lista))
    {
        return no;
    }
    if (lista->codigo > codigo)
    {
        no->proximo = lista;
        return no;
    }
    IndexExercicioCodigo *proximo = lista;
    while (proximo != NULL && proximo->proximo != NULL && proximo->proximo->codigo < codigo)
    {
        proximo = proximo->proximo;
    }
    no->proximo = proximo->proximo;
    proximo->proximo = no;
    return lista;
}

IndexExercicioCodigo* buscarIndexCodigoExercicio(IndexExercicioCodigo *lista, int codigo)
{
    if (isListaVaziaIndexExercicioCodigo(lista))
    {
        return NULL;
    }
    IndexExercicioCodigo* proximo = lista;
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

IndexExercicioCodigo* limparListaIndexCodigoExercicio(IndexExercicioCodigo* lista)
{
    if (!isListaVaziaIndexExercicioCodigo(lista))
    {
        lista->proximo = limparListaIndexCodigoExercicio(lista->proximo);
        free(lista);
    }
    return NULL;
}

IndexExercicioCodigo * removerIndexExercicioCodigo(IndexExercicioCodigo* lista, int codigo)
{
    if (isListaVaziaIndexExercicioCodigo(lista))
    {
        return lista;
    }
    IndexExercicioCodigo *no = lista, *proximo = lista;
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
        IndexExercicioCodigo* temp = proximo;
        no->proximo = proximo->proximo;
        free(temp);
    }
    return lista;
}


int isListaVaziaIndexExercicioCodigo(IndexExercicioCodigo* lista)
{
    if (lista == NULL)
    {
        return 1;
    }
    return 0;
}

int tamanhoListaIndexExercicioCodigo(IndexExercicioCodigo* lista)
{
    if (isListaVaziaIndexExercicioCodigo(lista) == 1)
    {
        return 0;
    }
    IndexExercicioCodigo* tmp = lista;
    int tamanhoLista = 0;
    while (tmp != NULL)
    {
        tmp = tmp->proximo;
        tamanhoLista++;
    }
    return tamanhoLista;
}

