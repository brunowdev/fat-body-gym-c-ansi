#include <stdlib.h>
#include <stdio.h>

#include "AlunoRepositorio.h"

AlunoRepositorio * criarAlunoRepositorio(IndexAlunoCodigo * indexAlunoCodigo, FILE * alunoTB)
{
    AlunoRepositorio * alunoRepo = (AlunoRepositorio *) malloc(sizeof(AlunoRepositorio));
    alunoRepo->alunoTB = alunoTB;
    alunoRepo->indexAlunoCodigo = indexAlunoCodigo;
    return alunoRepo;
}
