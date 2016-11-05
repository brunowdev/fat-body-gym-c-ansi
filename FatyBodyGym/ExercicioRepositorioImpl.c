#include <stdlib.h>
#include <stdio.h>

#include "ExercicioRepositorio.h"

ExercicioRepositorio * criarExercicioRepositorio(ExercicioRepositorio * indexExercicioCodigo, FILE * exercicioTB)
{
    ExercicioRepositorio * exercicioRepo = (ExercicioRepositorio *) malloc(sizeof(ExercicioRepositorio));
    exercicioRepo->exercicioTB = exercicioTB;
    exercicioRepo->indexExercicioCodigo = indexExercicioCodigo;
    return exercicioRepo;
}
