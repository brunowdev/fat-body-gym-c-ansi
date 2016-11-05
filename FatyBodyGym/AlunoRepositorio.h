#ifndef ALUNOREPOSITORIO_H_INCLUDED
#define ALUNOREPOSITORIO_H_INCLUDED

#include "IndexAlunoCodigo.h"
#include <stdio.h>

struct alunoRepositorio
{
    IndexAlunoCodigo * indexAlunoCodigo;
    FILE * alunoTB;
};

typedef struct alunoRepositorio AlunoRepositorio;

AlunoRepositorio * criarAlunoRepositorio(IndexAlunoCodigo * indexAlunoCodigo, FILE * alunoTB);

#endif // ALUNOREPOSITORIO_H_INCLUDED
