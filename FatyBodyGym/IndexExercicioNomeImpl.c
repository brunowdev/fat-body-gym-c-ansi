#include <stdio.h>
#include <stdlib.h>

#include "IndexExercicioNome.h"

IndexExercicioNome * criarListaIndexExercicioNome()
{
    return NULL;
}

IndexExercicioNome* criarNoIndexExercicioNome(char nome[120], int posicao)
{
    IndexExercicioNome* no = (IndexExercicioNome*) malloc(sizeof(IndexExercicioNome));
    strcpy(no->nome, nome);
    no->posicao = posicao;
    no->proximo = NULL;
    return no;
}

IndexExercicioNome* adicionarIndexExercicioNome(IndexExercicioNome *lista, char nome[120], int posicao)
{

    IndexExercicioNome * no = criarNoIndexExercicioNome(nome, posicao);
    if (isListaVaziaIndexExercicioNome(lista))
    {
        return no;
    }
    if (strcmp(lista->nome, nome) < 0)
    {
        no->proximo = lista;
        return no;
    }
    IndexExercicioNome *proximo = lista;
    while (proximo != NULL && proximo->proximo != NULL && strcmp(proximo->proximo->nome, nome) < 0)
    {
        proximo = proximo->proximo;
    }
    no->proximo = proximo->proximo;
    proximo->proximo = no;
    return lista;
}

IndexExercicioNome* buscarIndexExercicioNome(IndexExercicioNome *lista, char nome[120])
{
    if (isListaVaziaIndexExercicioNome(lista))
    {
        return NULL;
    }
    IndexExercicioNome* proximo = lista;
    while (proximo != NULL)
    {
        if (strcmp(proximo->nome, nome) == 0)
        {
            return proximo;
        }
        proximo = proximo->proximo;
    }
    return NULL;
}

IndexExercicioNome* removerIndexExercicioNome(IndexExercicioNome* lista, char nome[120])
{
    if (isListaVaziaIndexExercicioNome(lista))
    {
        return lista;
    }
    IndexExercicioNome *no = lista, *proximo = lista;
    if (strcmp(lista->nome, nome) == 0)
    {
        proximo = lista->proximo;
        free(lista);
        return proximo;
    }
    while (proximo != NULL && strcmp(proximo->nome, nome) != 0)
    {
        no = proximo;
        proximo = no->proximo;
    }
    if (proximo != NULL && strcmp(proximo->nome, nome) == 0)
    {
        IndexExercicioNome * temp = proximo;
        no->proximo = proximo->proximo;
        free(temp);
    }
    return lista;
}

IndexExercicioNome* limparListaIndexExercicioNome(IndexExercicioNome* lista)
{
    if (!isListaVaziaIndexExercicioNome(lista))
    {
        lista->proximo = limparListaIndexExercicioNome(lista->proximo);
        free(lista);
    }
    return NULL;
}

int isListaVaziaIndexExercicioNome(IndexExercicioNome* lista)
{
    if (lista == NULL)
    {
        return 1;
    }
    return 0;
}

int tamanhoListaIndexExercicioNome(IndexExercicioNome* lista)
{
    if (isListaVaziaIndexExercicioNome(lista) == 1)
    {
        return 0;
    }
    IndexExercicioNome* tmp = lista;
    int tamanhoLista = 0;
    while (tmp != NULL)
    {
        tmp = tmp->proximo;
        tamanhoLista++;
    }
    return tamanhoLista;
}
