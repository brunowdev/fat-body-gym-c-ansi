#include <stdlib.h>
#include "Exercicio.h"
#include "Constantes.h"

#include "IndexExercicioCodigo.h"
#include "IndexExercicioCodigoImpl.c"
#include "IndexExercicioNome.h"
#include "IndexExercicioNomeImpl.c"

Exercicio* criarExercicio()
{
    Exercicio* exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    printf("Informe os dados do exercício........:\n");
    printf("Código...............................:\n");
    scanf("%d", &exercicio->id);
    getchar();
    printf("Nome.................................:\n");
    fflush(stdin);
    gets(exercicio->nome);
    printf("Carga (Kg)...........................:\n");
    scanf("%f", &exercicio->carga);
    getchar();
    printf("Séries...............................:\n");
    scanf("%d", &exercicio->series);
    getchar();
    printf("Tempo (h)............................:\n");
    scanf("%d", &exercicio->tempo);
    getchar();
    exercicio->status = 1;
    return exercicio;
}

Exercicio * editarExercicio(Exercicio * exercicio)
{
    printf("Informe os dados atualizados.........:\n");
    printf("ID %-.15d (Não editável):\n", exercicio->id);
    printf("Nome.................................:\n");
    fflush(stdin);
    gets(exercicio->nome);
    printf("Carga (Kg)...........................:\n");
    scanf("%f", &exercicio->carga);
    getchar();
    printf("Séries...............................:\n");
    scanf("%d", &exercicio->series);
    getchar();
    printf("Tempo (h)............................:\n");
    scanf("%d", &exercicio->tempo);
    getchar();
    printf("Status...............................:\n");

    int status = 0;
    scanf("%d*", &status);
      getchar();

    if (status < 0 || status > 1)
      status = 0;

    exercicio->status = status;
    return exercicio;
}

IndexExercicioCodigo * carregarIndiceCodigoExercicio(const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb+");
    IndexExercicioCodigo * lista = criarListaIndexCodigoExercicio();
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo com os índices por \"Código\" da tabela \"Exercícios\".\n");
        getchar();
    }
    else
    {
        IndexExercicioCodigo * indExercicio = (IndexExercicioCodigo *) malloc(sizeof(IndexExercicioCodigo));
        fread(indExercicio, sizeof(IndexExercicioCodigo), 1, arquivo);
        while (!feof(arquivo))
        {
            lista = adicionarIndexCodigoExercicio(lista, indExercicio->codigo, indExercicio->posicao);
            fread(indExercicio, sizeof(IndexExercicioCodigo), 1, arquivo);
        }
        free(indExercicio);
        indExercicio = NULL;
    }
    return lista;
}

IndexExercicioNome* carregarIndiceNomeExercicio(const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb+");
    IndexExercicioNome* lista = criarListaIndexExercicioNome();
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo com os índices por \"Nome\" da tabela \"Exercícios\".\n");
        getchar();
    }
    else
    {
        IndexExercicioNome* indExercicio = (IndexExercicioNome*) malloc(sizeof(IndexExercicioNome));
        fread(indExercicio, sizeof(IndexExercicioNome), 1, arquivo);
        while (!feof(arquivo))
        {
            lista = adicionarIndexExercicioNome(lista, indExercicio->nome, indExercicio->posicao);
            fread(indExercicio, sizeof(IndexExercicioNome), 1, arquivo);
        }
        free(indExercicio);
        indExercicio = NULL;
    }
    return lista;
}

void listarTodosExercicios(FILE *arquivo, IndexExercicioCodigo * indice)
{
    rewind(arquivo);
    Exercicio *exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    if (exercicio == NULL)
    {
        printf("Não foi possível alocar memória para listar os exercícios.\n");
        exit(1);
        return;
    }
    int cont = 0;

    printf("%10s  %-20s  %8s  %8s  %8s  %8s\n", "ID", "Nome", "  Tempo", "  Séries", "   Carga", "  Status");
    printf("%10s  %20s  %8s  %8s  %8s  %8s\n", "==========", "====================", "========", "========","========", "========", "========");
    while (indice != NULL)
    {
        fseek(arquivo, indice->posicao * sizeof(Exercicio), SEEK_SET);
        fread(exercicio, sizeof(Exercicio), 1, arquivo);
        if (!feof(arquivo))
        {
            cont++;
            printf("%10d  %-20s  %8d  %8d  %8.2f  %8s\n", exercicio->id, exercicio->nome, exercicio->tempo,  exercicio->series, exercicio->carga, (exercicio->status == 1 ? "ATIVO" : (exercicio->status == 0 ? "INATIVO" : "EXCLUÍDO")));
        }
        indice = indice->proximo;
    }
    if (cont < 1)
    {
        printf("Não foi encontrado nenhum exercício na base de dados para ser exibido.\n");
    }
    free(exercicio);
    exercicio = NULL;
}

void listarTodosExerciciosAtivos(FILE *arquivo, IndexExercicioCodigo * indice)
{
    rewind(arquivo);
    Exercicio *exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    if (exercicio == NULL)
    {
        printf("Não foi possível alocar memória para listar os exercícios.\n");
        exit(1);
        return;
    }
    int cont = 0;
    printf("%10s  %-30s  %10s  %10s  %10s  %10s\n", "ID", "Nome", "Tempo", "Series","Carga", "Status");
    printf("%10s  %-30s  %10s  %10s  %10s  %10s\n", "==========", "==============================", "==========", "==========","==========", "==========");
    while (indice != NULL)
    {
        fseek(arquivo, indice->posicao * sizeof(Exercicio), SEEK_SET);
        fread(exercicio, sizeof(Exercicio), 1, arquivo);
        if (!feof(arquivo) && exercicio->status == 1)
        {
            cont++;
            printf("%10d  %-30s  %10d  %10d  %10.2f  %10s\n", exercicio->id, exercicio->nome, exercicio->tempo,exercicio->series, exercicio->carga, (exercicio->status == 1 ? "ATIVO" : "INATIVO"));
        }
        indice = indice->proximo;
    }
    if (cont < 1)
    {
        printf("Não foi encontrado nenhum exercício na base de dados para ser exibido.\n");
    }
    free(exercicio);
    exercicio = NULL;
}


int escreverExercicio(FILE *arquivo, Exercicio* exercicio)
{
    rewind(arquivo);
    int posicao = -1;
    Exercicio *tmpExercicio = (Exercicio*) malloc(sizeof(Exercicio));
    while (!feof(arquivo))
    {
        posicao++;
        fread(tmpExercicio, sizeof(Exercicio), 1, arquivo);

        // Considera primeiro os exercícios excluídos antes de ir para o final do arquivo
        if (!feof(arquivo) && tmpExercicio != NULL && tmpExercicio->status == -1)
        {
            break;
        }
    }
    fseek(arquivo, posicao * sizeof(Exercicio), SEEK_SET);
    fwrite(exercicio, sizeof(Exercicio), 1, arquivo);
    free(tmpExercicio);
    tmpExercicio = NULL;
    return posicao;
}

int atualizarExercicio(FILE *arquivo, Exercicio* exercicio)
{
    rewind(arquivo);
    int localizado = 0;
    int posicao = -1;
    Exercicio *tmpExercicio = (Exercicio*) malloc(sizeof(Exercicio));
    while (!feof(arquivo))
    {
        posicao++;
        fread(tmpExercicio, sizeof(Exercicio), 1, arquivo);

        // Considera primeiro os exercícios marcados como excluídos antes de ir para o final do arquivo
        if (!feof(arquivo) && tmpExercicio != NULL && tmpExercicio->id == exercicio->id)
        {
            localizado = 1;
            break;
        }
    }

    if (localizado)
    {
        fseek(arquivo, (posicao--) * sizeof(Exercicio), SEEK_SET);
        fwrite(exercicio, sizeof(Exercicio), 1, arquivo);
    }
    else
    {
        printf("Não foi encontrado nenhum exercício na base de dados com o código recebido.\n");
    }
    free(tmpExercicio);
    tmpExercicio = NULL;
    return posicao;
}

int excluirExercicio(FILE *arquivo, int codigoExercicio)
{

    rewind(arquivo);
    int localizado = 0;
    int posicao = -1;
    int fwresultado = 0;

    Exercicio *tmpExercicio = (Exercicio*) malloc(sizeof(Exercicio));
    while (!feof(arquivo))
    {
        posicao++;
        fread(tmpExercicio, sizeof(Exercicio), 1, arquivo);

        // Considera primeiro os exercícios excluídos antes de ir para o final do arquivo
        if (!feof(arquivo) && tmpExercicio != NULL && tmpExercicio->id == codigoExercicio)
        {
            localizado = 1;
            // Atualiza o registro para excluído
            tmpExercicio->status = -1;
            break;
        }
    }

    if (localizado)
    {
        fseek(arquivo, (posicao--) * sizeof(Exercicio), SEEK_SET);
        fwrite(tmpExercicio, sizeof(Exercicio), 1, arquivo);
    }
    else
    {
        printf("Não foi encontrado nenhum exercício na base de dados com o código recebido.\n");
    }
    free(tmpExercicio);
    tmpExercicio = NULL;
    return localizado;
}

void escreverIndiceCodigoExercicio(IndexExercicioCodigo * lista, const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir os índices existentes para a tabela de exercícios.");
        return;
    }
    while(lista != NULL)
    {
        fwrite(lista, sizeof(IndexExercicioCodigo), 1, arquivo);
        lista = lista->proximo;
    }
    fclose(arquivo);
}

void escreverIndiceNomeExercicio(IndexExercicioNome * lista, const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir os índices existentes para a tabela de exercícios.");
        return;
    }
    while(lista != NULL)
    {
        fwrite(lista, sizeof(IndexExercicioNome), 1, arquivo);
        lista = lista->proximo;
    }
    fclose(arquivo);
}

Exercicio* buscarPorCodigoExercicio(FILE *arquivo, IndexExercicioCodigo * indice, int codigo)
{
    IndexExercicioCodigo * index = NULL;
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
    fseek(arquivo, index->posicao * sizeof(Exercicio), SEEK_SET);
    Exercicio* exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    if (exercicio == NULL)
    {
        printf("Não foi possível alocar memória para efetuar busca exercício por código.\n");
        return NULL;
    }
    fread(exercicio, sizeof(Exercicio), 1, arquivo);
    return exercicio;
}

Exercicio* buscarPorNomeExercicio(FILE *arquivo, IndexExercicioNome* indice, char * nomeProcurado)
{
    IndexExercicioNome* indExercicio = NULL;
    while (indice != NULL && indExercicio == NULL)
    {
        if (strcmp(indice->nome, nomeProcurado) == 0)
        {
            indExercicio = indice;
        }
        indice = indice->proximo;
    }
    if (indExercicio == NULL)
    {
        return NULL;
    }
    fseek(arquivo, indExercicio->posicao * sizeof(Exercicio), SEEK_SET);
    Exercicio* exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    if (exercicio == NULL)
    {
        printf("Não foi possível alocar memória para efetuar consulta por Nome.\n");
        return NULL;
    }
    fread(exercicio, sizeof(Exercicio), 1, arquivo);

    if (exercicio == NULL || exercicio->status == -1)
      return NULL;

    return exercicio;
}

void imprimirExercicio(Exercicio * exercicio)
{
    printf("%10s  %-30s  %10s  %10s  %10s  %10s\n", "ID", "Nome", "Tempo", "Series","Carga", "Status");
    printf("%10s  %-30s  %10s  %10s  %10s  %10s\n", "==========", "==============================", "==========", "==========","==========", "==========");
    printf("%10d  %-30s  %10d  %10d  %10.2f  %10s\n", exercicio->id, exercicio->nome, exercicio->tempo,exercicio->series, exercicio->carga, (exercicio->status == 1 ? "ATIVO" : "INATIVO"));
}
