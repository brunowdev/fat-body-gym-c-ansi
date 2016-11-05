#ifndef EVOLUCAO_H_INCLUDED
#define EVOLUCAO_H_INCLUDED

struct evolucao
{

    int id;
    char observacoesPersonal[500];
    char observacoesAluno[500];
    char data[11];
    int medida_fk;

}

typedef struct evolucao Evolucao;

Evolucao * criarEvolucao();

#endif // EVOLUCAO_H_INCLUDED
