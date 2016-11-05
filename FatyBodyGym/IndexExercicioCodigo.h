#ifndef INDEXEXERCICIOCODIGO_H_INCLUDED
#define INDEXEXERCICIOCODIGO_H_INCLUDED

struct indexExercicioCodigo
{
    int codigo;
    int posicao;
    struct indexExercicioCodigo* proximo;
};

typedef struct indexExercicioCodigo IndexExercicioCodigo;

IndexExercicioCodigo * criarListaIndexCodigoExercicio();
IndexExercicioCodigo * criarNoIndexCodigoExercicio(int codigo, int posicao);
IndexExercicioCodigo * adicionarIndexCodigoExercicio(IndexExercicioCodigo * lista, int codigo, int posicao);
IndexExercicioCodigo * buscarIndexCodigoExercicio(IndexExercicioCodigo * lista, int codigo);
IndexExercicioCodigo * removerIndexExercicioCodigo(IndexExercicioCodigo* lista, int codigo);
IndexExercicioCodigo * limparListaIndexCodigoExercicio(IndexExercicioCodigo* lista);
int isListaVaziaIndexExercicioCodigo(IndexExercicioCodigo* lista);
int tamanhoListaIndexExercicioCodigo(IndexExercicioCodigo* lista);

#endif // INDEXEXERCICIOCODIGO_H_INCLUDED
