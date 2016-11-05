#ifndef EXERCICIOS_H_INCLUDED
#define EXERCICIOS_H_INCLUDED

#include "Exercicio.h"
#include "IndexExercicioCodigo.h"
#include "IndexExercicioNome.h"

Exercicio * criarExercicio();
Exercicio * editarExercicio(Exercicio * exercicio);
int excluirExercicio(FILE *arquivo, int codigoExercicio);
void listarTodosExercicios(FILE *arquivo, IndexExercicioCodigo * indice);
void listarTodosExerciciosAtivos(FILE *arquivo, IndexExercicioCodigo * indice);
IndexExercicioCodigo * carregarIndiceCodigoExercicio(const char* nomeArquivo);
IndexExercicioNome * carregarIndiceNomeExercicio(const char* nomeArquivo);
void escreverIndiceCodigoExercicio(IndexExercicioCodigo * lista, const char* nomeArquivo);
void escreverIndiceNomeExercicio(IndexExercicioNome * lista, const char* nomeArquivo);
Exercicio* buscarPorCodigoExercicio(FILE *arquivo, IndexExercicioCodigo * indice, int codigo);
Exercicio* buscarPorNomeExercicio(FILE *arquivo, IndexExercicioNome * indice, char* nome);

#endif // EXERCICIOS_H_INCLUDED
