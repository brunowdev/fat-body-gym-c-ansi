#ifndef INDEXTREINOALUNO_H_INCLUDED
#define INDEXTREINOALUNO_H_INCLUDED

struct indexTreinoAluno
{
    int codigo;
    int posicao;
    struct indexTreinoAluno * proximo;
};

typedef struct indexTreinoAluno IndexTreinoAluno;

IndexTreinoAluno * criarListaIndexTreinoAluno();
IndexTreinoAluno * criarNoIndexTreinoAluno(int codigo, int posicao);
IndexTreinoAluno * adicionarIndexTreinoAluno(IndexTreinoAluno * lista, int codigo, int posicao);
IndexTreinoAluno * buscarIndexTreinoAluno(IndexTreinoAluno * lista, int codigo);
IndexTreinoAluno * removerIndexTreinoAluno(IndexTreinoAluno* lista, int codigo);
IndexTreinoAluno * limparListaIndexTreinoAluno(IndexTreinoAluno* lista);
int isListaVaziaIndexTreinoAluno(IndexTreinoAluno* lista);
int tamanhoListaIndexTreinoAluno(IndexTreinoAluno* lista);


#endif // INDEXTREINOALUNO_H_INCLUDED
