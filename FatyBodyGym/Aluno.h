#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED

struct aluno
{

    int id;
    char nome[120];
    char cadastro[11];
    char cpf[15];
    int idade;
    int sexo;
    float peso;
    float peito;
    float braco;
    float abdomem;
    float quadril;
    float coxa;
    float panturrilha;
    // 1 - Ativo 0 - Inativo -1 - Excluído
    int status;

};

typedef struct aluno Aluno;

#endif // ALUNO_H_INCLUDED
