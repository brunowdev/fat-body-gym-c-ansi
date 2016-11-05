#ifndef INDEXALUNOCODIGO_H_INCLUDED
#define INDEXALUNOCODIGO_H_INCLUDED

struct indexAlunoCodigo
{
    int codigo;
    int posicao;
    struct indexAlunoCodigo* proximo;
};

typedef struct indexAlunoCodigo IndexAlunoCodigo;

IndexAlunoCodigo * criarListaIndexCodigo();
IndexAlunoCodigo * criarNoIndexCodigo(int codigo, int posicao);
IndexAlunoCodigo * adicionarIndexCodigo(IndexAlunoCodigo * lista, int codigo, int posicao);
IndexAlunoCodigo * buscarIndexCodigo(IndexAlunoCodigo * lista, int codigo);
IndexAlunoCodigo * removerIndexCodigo(IndexAlunoCodigo* lista, int codigo);
IndexAlunoCodigo * limparListaIndexCodigo(IndexAlunoCodigo* lista);
int isListaVaziaIndexAlunoCodigo(IndexAlunoCodigo* lista);
int tamanhoListaIndexAlunoCodigo(IndexAlunoCodigo* lista);

#endif // INDEXALUNOCODIGO_H_INCLUDED
