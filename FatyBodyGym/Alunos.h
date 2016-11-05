#ifndef ALUNOS_H_INCLUDED
#define ALUNOS_H_INCLUDED

#include "Aluno.h"
#include "IndexAlunoCodigo.h"
#include "IndexAlunoCPF.h"

Aluno * criarAluno();
Aluno * editarAluno(Aluno * aluno);
int excluirAluno(FILE *arquivo, int codigoAluno);
IndexAlunoCodigo * carregarIndiceCodigo(const char* nomeArquivo);
IndexAlunoCPF * carregarIndiceCPF(const char* nomeArquivo);
void listarTodos(FILE *arquivo, IndexAlunoCodigo * indice);
void listarTodosAlunosAtivos(FILE *arquivo, IndexAlunoCodigo * indice);
void escreverIndiceCodigo(IndexAlunoCodigo * lista, const char* nomeArquivo);
void escreverIndiceCPF(IndexAlunoCPF * lista, const char* nomeArquivo);
Aluno* buscarPorCodigo(FILE *arquivo, IndexAlunoCodigo * indice, int codigo);
Aluno* buscarPorCPF(FILE *arquivo, IndexAlunoCPF * indice, char* cpf);

#endif // ALUNOS_H_INCLUDED
