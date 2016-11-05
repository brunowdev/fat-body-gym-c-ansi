#ifndef EXERCICIOREPOSITORIO_H_INCLUDED
#define EXERCICIOREPOSITORIO_H_INCLUDED

#include "IndexExercicioCodigo.h"
#include <stdio.h>

struct exercicioRepositorio
{
  IndexExercicioCodigo * indexExercicioCodigo;
  FILE * exercicioTB;
};

typedef struct exercicioRepositorio ExercicioRepositorio;

ExercicioRepositorio * criarExercicioRepositorio(ExercicioRepositorio * indexExercicioCodigo, FILE * exercicioTB);

#endif // EXERCICIOREPOSITORIO_H_INCLUDED
