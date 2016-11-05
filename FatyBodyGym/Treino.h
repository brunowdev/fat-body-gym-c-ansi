#ifndef TREINO_H_INCLUDED
#define TREINO_H_INCLUDED

struct treino
{
    int id;
    int idAluno;
    int idExercicio;
    float tempo;
    char dataTreino[12];
};

typedef struct treino Treino;

#endif // TREINO_H_INCLUDED
