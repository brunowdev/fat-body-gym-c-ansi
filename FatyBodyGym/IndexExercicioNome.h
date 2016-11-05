#ifndef INDEXEXERCICIONOME_H_INCLUDED
#define INDEXEXERCICIONOME_H_INCLUDED

struct indexExercicioNome
{
    char nome[120];
    int posicao;
    struct indexExercicioNome * proximo;
};

typedef struct indexExercicioNome IndexExercicioNome;

IndexExercicioNome* criarListaIndexExercicioNome();
IndexExercicioNome* adicionarIndexExercicioNome(IndexExercicioNome * lista, char nome[120], int posicao);
IndexExercicioNome* buscarIndexExercicioNome(IndexExercicioNome * lista, char nome[120]);
IndexExercicioNome* removerIndexExercicioNome(IndexExercicioNome* lista, char nome[120]);
IndexExercicioNome* limparListaIndexExercicioNome(IndexExercicioNome * lista);
int isListaVaziaIndexExercicioNome(IndexExercicioNome * lista);

#endif // INDEXEXERCICIONOME_H_INCLUDED
