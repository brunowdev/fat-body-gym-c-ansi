#ifndef EXERCICIO_H_INCLUDED
#define EXERCICIO_H_INCLUDED

struct exercicio
{
    int id;
    char nome[120];
    int tempo;
    int series;
    float carga;
    int status;
};

typedef struct exercicio Exercicio;

Exercicio* criarExercicio();

#endif // EXERCICIO_H_INCLUDED
