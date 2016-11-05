#include <stdlib.h>
#include <stdio.h>

#include "TreinoRepositorio.h"

TreinoRepositorio * criarTreinoRepositorio(IndexTreinoAluno * indexTreinoAluno, FILE * treinoTB)
{
    TreinoRepositorio * treinoRepo = (TreinoRepositorio *) malloc(sizeof(TreinoRepositorio));
    treinoRepo->treinoTB = treinoTB;
    treinoRepo->indexTreinoAluno = indexTreinoAluno;
    return treinoRepo;
}
