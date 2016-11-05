#ifndef TREINOREPOSITORIO_H_INCLUDED
#define TREINOREPOSITORIO_H_INCLUDED

#include "IndexTreinoAluno.h"
#include <stdio.h>

struct treinoRepositorio
{
  IndexTreinoAluno * indexTreinoAluno;
  FILE * treinoTB;
};

typedef struct treinoRepositorio TreinoRepositorio;

#endif // TREINOREPOSITORIO_H_INCLUDED
