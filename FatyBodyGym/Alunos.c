#include <stdlib.h>
#include "Alunos.h"
#include "Aluno.h"
#include "Constantes.h"

#include "IndexAlunoCodigo.h"
#include "IndexAlunoCodigoImpl.c"
#include "IndexAlunoCPF.h"
#include "IndexAlunoCPFImpl.c"

Aluno* criarAluno()
{
    Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));
    printf("Informe os dados do Aluno........:\n");
    printf("Matricula........................:\n");
    scanf("%d", &aluno->id);
    getchar();
    printf("Nome.............................:\n");
    fflush(stdin);
    gets(aluno->nome);
    printf("CPF..............................:\n");
    fflush(stdin);
    gets(aluno->cpf);
    printf("Idade............................:\n");
    scanf("%d%*c", &aluno->idade);
    printf("Sexo.............................:\n");
    printf("0 - Masculino ou 1 - Feminino     \n");
    scanf("%d%*c", &aluno->sexo);
    printf("Data cadastro....................:\n");
    printf("Formato: dd-mm-aaaa     \n");
    fflush(stdin);
    gets(aluno->cadastro);
    printf("Peso (kg)........................:\n");
    scanf("%f", &aluno->peso);
    getchar();
    printf("Peito (cm).......................:\n");
    scanf("%f", &aluno->peito);
    getchar();
    printf("Abdomem (cm).....................:\n");
    scanf("%f", &aluno->abdomem);
    getchar();
    printf("Braço (cm).......................:\n");
    scanf("%f", &aluno->braco);
    getchar();
    printf("Coxa (cm)........................:\n");
    scanf("%f", &aluno->coxa);
    getchar();
    printf("Quadril (cm).....................:\n");
    scanf("%f", &aluno->quadril);
    getchar();
    printf("Panturrilha (cm).................:\n");
    scanf("%f", &aluno->panturrilha);
    getchar();
    aluno->status = 1;
    return aluno;
}

Aluno * editarAluno(Aluno * aluno)
{
    printf("Informe os dados atualizados.....:\n");
    printf("ID %-.15d (Não editável):\n", aluno->id);
    printf("Nome.............................:\n");
    fflush(stdin);
    gets(aluno->nome);
    printf("CPF..............................:\n");
    fflush(stdin);
    gets(aluno->cpf);
    printf("Idade............................:\n");
    scanf("%d%*c", &aluno->idade);
    printf("Sexo.............................:\n");
    printf("0 - Masculino ou 1 - Feminino     \n");
    scanf("%d%*c", &aluno->sexo);
    printf("Data cadastro....................:\n");
    printf("Formato: dd-mm-aaaa     \n");
    fflush(stdin);
    gets(aluno->cadastro);
    printf("Peso (kg)........................:\n");
    scanf("%f", &aluno->peso);
    getchar();
    printf("Peito (cm).......................:\n");
    scanf("%f", &aluno->peito);
    getchar();
    printf("Abdomem (cm).....................:\n");
    scanf("%f", &aluno->abdomem);
    getchar();
    printf("Braço (cm).......................:\n");
    scanf("%f", &aluno->braco);
    getchar();
    printf("Coxa (cm)........................:\n");
    scanf("%f", &aluno->coxa);
    getchar();
    printf("Quadril (cm).....................:\n");
    scanf("%f", &aluno->quadril);
    getchar();
    printf("Panturrilha (cm).................:\n");
    scanf("%f", &aluno->panturrilha);
    getchar();

    printf("Status...............................:\n");

    int status = 0;
    scanf("%d*", &status);
      getchar();

    if (status < 0 || status > 1)
      status = 0;

    aluno->status = status;
    return aluno;
}

IndexAlunoCodigo * carregarIndiceCodigo(const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb+");
    IndexAlunoCodigo * lista = criarListaIndexCodigo();
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo com os índices por \"Nome\" da tabela \"Alunos\".\n");
        getchar();
    }
    else
    {
        IndexAlunoCodigo * indAluno = (IndexAlunoCodigo *) malloc(sizeof(IndexAlunoCodigo));
        fread(indAluno, sizeof(IndexAlunoCodigo), 1, arquivo);
        while (!feof(arquivo))
        {
            lista = adicionarIndexCodigo(lista, indAluno->codigo, indAluno->posicao);
            fread(indAluno, sizeof(IndexAlunoCodigo), 1, arquivo);
        }
        free(indAluno);
        indAluno = NULL;
    }
    return lista;
}

IndexAlunoCPF* carregarIndiceCPF(const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb+");
    IndexAlunoCPF* lista = criarListaIndexCPF();
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo com os índices por \"CPF\" da tabela \"Alunos\".\n");
        getchar();
    }
    else
    {
        IndexAlunoCPF* indAluno = (IndexAlunoCPF*) malloc(sizeof(IndexAlunoCPF));
        fread(indAluno, sizeof(IndexAlunoCPF), 1, arquivo);
        while (!feof(arquivo))
        {
            lista = adicionarIndexCPF(lista, indAluno->cpf, indAluno->posicao);
            fread(indAluno, sizeof(IndexAlunoCPF), 1, arquivo);
        }
        free(indAluno);
        indAluno = NULL;
    }
    return lista;
}


void listarTodos(FILE *arquivo, IndexAlunoCodigo * indice)
{
    rewind(arquivo);
    Aluno *aluno = (Aluno*) malloc(sizeof(Aluno));
    if (aluno == NULL)
    {
        printf("Não foi possível alocar memória para listar os alunos\n");
        exit(1);
        return;
    }
    int num = 0;

    printf("%10s  %-24s  %-14s  %6s  %4s  %13s  %6s\n", "ID", "Nome", "CPF ", "Idade","Sexo", "Data cadastro", "Status");
    printf("%10s  %24s  %14s  %6s  %4s  %13s  %6s\n", "==========", "========================", "==============", "======","====", "=============", "======");
    while (indice != NULL)
    {
        fseek(arquivo, indice->posicao * sizeof(Aluno), SEEK_SET);
        fread(aluno, sizeof(Aluno), 1, arquivo);
        if (!feof(arquivo) && aluno->status >= 0)
        {
            num++;
            printf("%10d  %-24s  %-14s  %6d  %4s  %13s  %6s\n", aluno->id, aluno->nome, aluno->cpf, aluno->idade, (aluno->sexo == 0 ? "MASC" : "FEM"), aluno->cadastro, (aluno->status == 1 ? "ATIVO" : "INATIVO"));
        }
        indice = indice->proximo;
    }
    if (num < 1)
    {
        printf("Não foi encontrado nenhum aluno na base de dados para ser exibido.\n");
    }
    free(aluno);
    aluno = NULL;
}

void listarTodosAlunosAtivos(FILE *arquivo, IndexAlunoCodigo * indice)
{
    rewind(arquivo);
    Aluno *aluno = (Aluno*) malloc(sizeof(Aluno));
    if (aluno == NULL)
    {
        printf("Não foi possível alocar memória para listar os alunos ativos\n");
        exit(1);
        return;
    }
    int num = 0;

    printf("%10s  %-24s  %-14s  %6s  %4s  %13s  %6s\n", "ID", "Nome", "CPF ", "Idade","Sexo", "Data cadastro", "Status");
    printf("%10s  %24s  %14s  %6s  %4s  %13s  %6s\n", "==========", "========================", "==============", "======","====", "=============", "======");
    while (indice != NULL)
    {
        fseek(arquivo, indice->posicao * sizeof(Aluno), SEEK_SET);
        fread(aluno, sizeof(Aluno), 1, arquivo);
        if (!feof(arquivo)  && aluno->status==1)
        {
            num++;
            printf("%10d  %-24s  %-14s  %6d  %4s  %13s  %6s\n", aluno->id, aluno->nome, aluno->cpf, aluno->idade, (aluno->sexo == 0 ? "MASC" : "FEM"), aluno->cadastro, (aluno->status == 1 ? "ATIVO" : "INATIVO"));
        }
        indice = indice->proximo;
    }
    if (num < 1)
    {
        printf("Não foi encontrado nenhum aluno na base de dados para ser exibido.\n");
    }
    free(aluno);
    aluno = NULL;
}


int escreverAluno(FILE *arquivo, Aluno* aluno)
{
    rewind(arquivo);
    int posicao = -1;
    Aluno *tmpAluno = (Aluno*) malloc(sizeof(Aluno));
    while (!feof(arquivo))
    {
        posicao++;
        fread(tmpAluno, sizeof(Aluno), 1, arquivo);

        // Considera primeiro os alunos excluídos antes de ir para o final do arquivo
        if (!feof(arquivo) && tmpAluno != NULL && tmpAluno->status == -1)
        {
            break;
        }
    }
    fseek(arquivo, posicao * sizeof(Aluno), SEEK_SET);
    fwrite(aluno, sizeof(Aluno), 1, arquivo);
    free(tmpAluno);
    tmpAluno = NULL;
    return posicao;
}

int atualizarAluno(FILE *arquivo, Aluno* aluno)
{
    rewind(arquivo);
    int localizado = 0;
    int posicao = -1;
    Aluno *tmpAluno = (Aluno*) malloc(sizeof(Aluno));
    while (!feof(arquivo))
    {
        posicao++;
        fread(tmpAluno, sizeof(Aluno), 1, arquivo);

        // Considera primeiro os alunos excluídos antes de ir para o final do arquivo
        if (!feof(arquivo) && tmpAluno != NULL && tmpAluno->id == aluno->id)
        {
            localizado = 1;
            break;
        }
    }

    if (localizado)
    {
        fseek(arquivo, posicao * sizeof(Aluno), SEEK_SET);
        fwrite(aluno, sizeof(Aluno), 1, arquivo);
    }
    else
    {
        printf("Não foi encontrado nenhum aluno na base de dados com o código recebido. Isto não é um bom sinal.\n");
    }
    free(tmpAluno);
    tmpAluno = NULL;
    return posicao;
}

int excluirAluno(FILE *arquivo, int codigoAluno)
{

    rewind(arquivo);
    int localizado = 0;
    int posicao = -1;
    int fwresultado = 0;

    Aluno *tmpAluno = (Aluno*) malloc(sizeof(Aluno));
    while (!feof(arquivo))
    {
        posicao++;
        fread(tmpAluno, sizeof(Aluno), 1, arquivo);

        // Considera primeiro os alunos excluídos antes de ir para o final do arquivo
        if (!feof(arquivo) && tmpAluno != NULL && tmpAluno->id == codigoAluno)
        {
            localizado = 1;
            // Atualiza o registro para excluído
            tmpAluno->status = -1;
            break;
        }
    }

    if (localizado)
    {
        fseek(arquivo, (posicao--) * sizeof(Aluno), SEEK_SET);

        fwrite(tmpAluno, sizeof(Aluno), 1, arquivo);
    }
    else
    {
        printf("Não foi encontrado nenhum aluno na base de dados com o código recebido.\n");
    }
    free(tmpAluno);
    tmpAluno = NULL;
    return localizado;
}


void escreverIndiceCodigo(IndexAlunoCodigo * lista, const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir os índices existentes para a tabela de alunos.");
        return;
    }
    while(lista != NULL)
    {
        fwrite(lista, sizeof(IndexAlunoCodigo), 1, arquivo);
        lista = lista->proximo;
    }
    fclose(arquivo);
}

void escreverIndiceCPF(IndexAlunoCPF * lista, const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir os índices existentes para a tabela de alunos.");
        return;
    }
    while(lista != NULL)
    {
        fwrite(lista, sizeof(IndexAlunoCPF), 1, arquivo);
        lista = lista->proximo;
    }
    fclose(arquivo);
}

Aluno* buscarPorCodigo(FILE *arquivo, IndexAlunoCodigo * indice, int codigo)
{
    IndexAlunoCodigo * index = NULL;
    while (indice != NULL && index == NULL)
    {
        if (indice->codigo == codigo)
        {
            index = indice;
        }
        indice = indice->proximo;
    }
    if (index == NULL)
    {
        return NULL;
    }
    fseek(arquivo, index->posicao * sizeof(Aluno), SEEK_SET);
    Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));
    if (aluno == NULL)
    {
        printf("Não foi possível alocar memória para efetuar busca por código.\n");
        return NULL;
    }
    fread(aluno, sizeof(Aluno), 1, arquivo);
    return aluno;
}

Aluno* buscarPorCPF(FILE *arquivo, IndexAlunoCPF* indice, char * cpfProcurado)
{
    IndexAlunoCPF* indAluno = NULL;
    while (indice != NULL && indAluno == NULL)
    {
        if (strcmp(indice->cpf, cpfProcurado) == 0)
        {
            indAluno = indice;
        }
        indice = indice->proximo;
    }
    if (indAluno == NULL)
    {
        return NULL;
    }
    fseek(arquivo, indAluno->posicao * sizeof(Aluno), SEEK_SET);
    Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));
    if (aluno == NULL)
    {
        printf("Não foi possível alocar memória para efetuar consulta por CPF.\n");
        return NULL;
    }
    fread(aluno, sizeof(Aluno), 1, arquivo);
    return aluno;
}

void imprimirAluno(Aluno * aluno)
{
    printf("%10s  %-24s  %-14s  %6s  %4s  %13s  %6s\n", "ID", "Nome", "CPF ", "Idade","Sexo", "Data cadastro", "Status");
    printf("%10s  %24s  %14s  %6s  %4s  %13s  %6s\n", "==========", "========================", "==============", "======","====", "=============", "======");
    printf("%10d  %-24s  %-14s  %6d  %4s  %13s  %6s\n", aluno->id, aluno->nome, aluno->cpf, aluno->idade, (aluno->sexo == 0 ? "MASC" : "FEM"), aluno->cadastro, (aluno->status == 1 ? "ATIVO" : "INATIVO"));
}
