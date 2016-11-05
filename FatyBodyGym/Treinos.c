#include <stdlib.h>

#include "Exercicio.h"
#include "Constantes.h"
#include "IndexTreinoAluno.h"
#include "IndexTreinoAlunoImpl.c"

#include "AlunoRepositorio.h"
#include "ExercicioRepositorio.h"
#include "TreinoRepositorio.h"

Treino* treinar(Aluno * aluno, Exercicio * exercicio)
{
    Treino * treino = (Treino*) malloc(sizeof(Treino));
    printf("Informe os dados do Aluno.............:\n");
    printf("Código treino.........................:\n");
    scanf("%d", &treino->id);
    getchar();
    printf("Tempo do treino em minutos (ex: 2.5)..:\n");
    scanf("%f%*c", &treino->tempo);
    char * dataTreino = malloc(12 * sizeof(char));
    printf("Data cadastro.........................:\n");
    printf("Formato: dd-mm-aaaa     \n");
    fflush(stdin);
    gets( treino->dataTreino );
    treino->idAluno = aluno->id;
    treino->idExercicio = exercicio->id;
    return treino;
}

IndexTreinoAluno * carregarIndiceTreinoAluno(const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb+");
    IndexTreinoAluno * lista = criarListaIndexTreinoAluno();
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo com os índices por \"Aluno\" da tabela \"Treinos\".\n");;
        getchar();
    }
    else
    {
        IndexTreinoAluno * idx = (IndexTreinoAluno *) malloc(sizeof(IndexTreinoAluno));
        fread(idx, sizeof(IndexTreinoAluno), 1, arquivo);
        while (!feof(arquivo))
        {
            lista = adicionarIndexTreinoAluno(lista, idx->codigo, idx->posicao);
            fread(idx, sizeof(IndexTreinoAluno), 1, arquivo);
        }
        free(idx);
        idx = NULL;
    }
    return lista;
}

void escreverIndiceTreino(IndexTreinoAluno * lista, const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir os índices existentes para a tabela de treinos.");
        return;
    }
    while(lista != NULL)
    {
        fwrite(lista, sizeof(IndexTreinoAluno), 1, arquivo);
        lista = lista->proximo;
    }
    fclose(arquivo);
}

int escreverTreino(FILE *arquivo, Treino* treino)
{
    rewind(arquivo);
    int posicao = -1;
    Treino *temp = (Treino*) malloc(sizeof(Treino));
    while (!feof(arquivo))
    {
        posicao++;
        fread(temp, sizeof(Treino), 1, arquivo);
    }
    fseek(arquivo, posicao * sizeof(Treino), SEEK_SET);
    fwrite(treino, sizeof(Treino), 1, arquivo);
    free(temp);
    temp = NULL;
    return posicao;
}

void listarTodosTreinos(AlunoRepositorio * alunoRep, ExercicioRepositorio * exercicioRep, TreinoRepositorio * treinoRep)
{

    FILE * fExercicios = exercicioRep->exercicioTB;
    FILE * fAlunos = alunoRep->alunoTB;
    FILE * fTreinos = treinoRep->treinoTB;
    IndexTreinoAluno * indTreinos = treinoRep->indexTreinoAluno;
    IndexAlunoCodigo * indAlunos;
    IndexExercicioCodigo * indExercicio ;

    rewind(fTreinos);
    Treino *treino = (Treino*) malloc(sizeof(Treino));
    if (treino == NULL)
    {
        printf("Não foi possível alocar memória para listar os treinos\n");
        exit(1);
        return;
    }
    int cont = 0;

    printf("%10s  %-10s  %-20s  %-20s  %5s\n", "ID", "Data", "Aluno", "Exercício", "Tempo");
    printf("%10s  %10s  %20s  %20s  %5s\n", "==========", "==========", "====================", "====================","=====");
    while (indTreinos != NULL)
    {

        fseek(fTreinos, indTreinos->posicao * sizeof(Treino), SEEK_SET);
        fread(treino, sizeof(Treino), 1, fTreinos);
        if (!feof(fTreinos))
        {

            indAlunos = alunoRep->indexAlunoCodigo;
            indExercicio = exercicioRep->indexExercicioCodigo;

            Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));
            Exercicio* exercicio = (Exercicio*) malloc(sizeof(Exercicio));

            // Localiza o aluno
            while (indAlunos != NULL)
            {
                if (indAlunos->codigo == treino->idAluno)
                {
                    break;
                }
                indAlunos = indAlunos->proximo;
            }

            fseek(fAlunos, indAlunos->posicao * sizeof(Aluno), SEEK_SET);
            fread(aluno, sizeof(Aluno), 1, fAlunos);

            // Localiza o exercício
            while (indExercicio != NULL)
            {
                if (indExercicio->codigo == treino->idExercicio)
                {
                    break;
                }
                indExercicio = indExercicio->proximo;
            }

            if (indExercicio != NULL)
            {
                fseek(fExercicios, indExercicio->posicao * sizeof(Exercicio), SEEK_SET);
                fread(exercicio, sizeof(Exercicio), 1, fExercicios);
            }
            else
            {
                exercicio = NULL;
            }

            cont++;
            printf("%10d  %-10s  %-20s  %-20s  %5.2f\n", treino->id, treino->dataTreino, (aluno == NULL ? "<EXCLUÍDO>" : aluno->nome), (exercicio == NULL ? "<EXCLUÍDO>" : exercicio->nome), treino->tempo);

            free(aluno);
            free(exercicio);
        }

        indTreinos = indTreinos->proximo;

    }
    if (cont < 1)
    {
        printf("Não foi encontrado nenhum treino na base de dados para ser exibido.\n");
    }
    free(treino);
    treino = NULL;
}


