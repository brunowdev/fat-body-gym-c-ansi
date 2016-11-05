#ifndef TREINOS_H_INCLUDED
#define TREINOS_H_INCLUDED

#include "AlunoRepositorio.h"
#include "ExercicioRepositorio.h"
#include "TreinoRepositorio.h"

Treino* treinar(Aluno * aluno, Exercicio * exercicio);
IndexTreinoAluno * carregarIndiceTreinoAluno(const char* nomeArquivo);
void listarTodosTreinos(AlunoRepositorio * alunoRepo, ExercicioRepositorio * exercicioRepo, TreinoRepositorio * treinoRepo);
void listarTodosTreinosPorAluno(FILE *arquivo, IndexTreinoAluno * indice);
void listarTodosTreinosNaData(FILE *arquivo, char * data);
void escreverIndiceTreino(IndexTreinoAluno * lista, const char* nomeArquivo);

#endif // TREINOS_H_INCLUDED
