#include <stdio.h>
#include <stdlib.h>

#include "TreinoRepositorio.h"
#include "AlunoRepositorio.h"
#include "ExercicioRepositorio.h"
#include "Exercicio.h"
#include "Treino.h"
#include "Aluno.h"

/**
 * Este relatório exibe cada exercício, quais alunos já o fizeram e quantas vezes foram feitas. Agrupa informações de três tabelas.
 */
void relatorioAlunosAgrupadosPorExercicio(AlunoRepositorio * alunoRep, ExercicioRepositorio * exercicioRep, TreinoRepositorio * treinoRep)
{

    char * nomeCaminhoArquivo = lerTexto("Informe o arquivo para impressão do relatório.", 120);
    FILE* arquivoRelatorio = fopen(nomeCaminhoArquivo, "w");
    if (arquivoRelatorio == NULL)
    {
        perror("Não foi possível abrir o arquivo informado.");
        return;
    }

    // Copia os ponteiros dos repositórios para não alterar os originais
    FILE * fExercicios = exercicioRep->exercicioTB;
    FILE * fAlunos = alunoRep->alunoTB;
    FILE * fTreinos = treinoRep->treinoTB;
    IndexAlunoCodigo * indAlunos = alunoRep->indexAlunoCodigo;
    IndexExercicioCodigo * indExercicio = exercicioRep->indexExercicioCodigo;
    IndexTreinoAluno * indTreinos = treinoRep->indexTreinoAluno;

    Exercicio * exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    Aluno * aluno = (Aluno *) malloc(sizeof(Aluno));
    Treino * treino = (Treino *) malloc(sizeof(Treino));
    fprintf(arquivoRelatorio, "%7s  %-42s  %-35s  %23s\n", " Código", "Exercício", " Aluno ", " Total de vezes praticou");
    fprintf(arquivoRelatorio, "%7s  %42s  %35s  %23s\n", "=======", "==========================================", "===================================","=======================");

    while (indExercicio != NULL)
    {


        if (exercicio == NULL || aluno == NULL || treino == NULL)
        {
            perror("Não existe memória disponível para gerar este o relatório solicitado.");
            return;
        }

        fseek(fExercicios, indExercicio->posicao * sizeof(Exercicio), SEEK_SET);
        fread(exercicio, sizeof(Exercicio), 1, fExercicios);


        if (exercicio->status == 1)
        {

            fprintf(arquivoRelatorio, "\n%7d  %-42s  ", exercicio->id, exercicio->nome);

            int qtdEx;

            indAlunos = alunoRep->indexAlunoCodigo;

            while (indAlunos != NULL)
            {

                fseek(fAlunos, indAlunos->posicao * sizeof(Aluno), SEEK_SET);

                fread(aluno, sizeof(Aluno), 1, fAlunos);
                indTreinos = treinoRep->indexTreinoAluno;

                qtdEx = 0;

                if (!feof(fAlunos) && aluno != NULL)
                {
                    while (indTreinos != NULL)
                    {
                        fseek(fTreinos, indTreinos->posicao * sizeof(Treino), SEEK_SET);
                        fread(treino, sizeof(Treino), 1, fTreinos);
                        if (!feof(fTreinos)  && treino != NULL)
                        {

                            if (treino->idAluno == aluno->id && treino->idExercicio == exercicio->id)
                            {
                                qtdEx++;
                            }

                            indTreinos = indTreinos->proximo;
                        }
                    }
                    indAlunos = indAlunos->proximo;
                    fprintf(arquivoRelatorio, "\n%-51s  %-35s  %23d\n", " ",aluno->nome, qtdEx);
                }
            }
        }
        indExercicio = indExercicio->proximo;
    }

    liberarPonteiro(exercicio);
    liberarPonteiro(aluno);
    liberarPonteiro(treino);
    fclose(arquivoRelatorio);
    printf("O relatório foi gerado com sucesso!", nomeCaminhoArquivo);

}

/**
 * Este relatório exibe cada aluno, quais alunos e quais treinos o mesmo fez. Também Agrupa informações de três tabelas.
 */
void relatorioTreinosAgrupadosPorAluno(AlunoRepositorio * alunoRep, ExercicioRepositorio * exercicioRep, TreinoRepositorio * treinoRep)
{

    char * nomeCaminhoArquivo = lerTexto("Informe o arquivo para impressão do relatório.", 120);
    FILE* arquivoRelatorio = fopen(nomeCaminhoArquivo, "w");
    if (arquivoRelatorio == NULL)
    {
        perror("Não foi possível abrir o arquivo informado.");
        return;
    }

    // Copia os ponteiros dos repositórios para não alterar os originais
    FILE * fExercicios = exercicioRep->exercicioTB;
    FILE * fAlunos = alunoRep->alunoTB;
    FILE * fTreinos = treinoRep->treinoTB;
    IndexAlunoCodigo * indAlunos = alunoRep->indexAlunoCodigo;
    IndexExercicioCodigo * indExercicio = exercicioRep->indexExercicioCodigo;
    IndexTreinoAluno * indTreinos = treinoRep->indexTreinoAluno;

    Exercicio* exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    Aluno * aluno = (Aluno *) malloc(sizeof(Aluno));
    Treino * treino = (Treino *) malloc(sizeof(Treino));
    fprintf(arquivoRelatorio, "%10s  %-42s  %-35s  %-10s  %10s  %10s\n", "ID", "Aluno", "Exercicio", "Data", "Tempo", "Carga");
    fprintf(arquivoRelatorio, "%10s  %42s  %35s  %10s  %10s  %10s\n", "=======", "==========================================", "===================================","==========", "==========", "==========");

    while (indAlunos != NULL)
    {

        if (exercicio == NULL || aluno == NULL || treino == NULL)
        {
            perror("Não existe memória disponível para gerar este o relatório solicitado.");
            return;
        }

        fseek(fAlunos, indAlunos->posicao * sizeof(Aluno), SEEK_SET);
        fread(aluno, sizeof(Aluno), 1, fAlunos);
        indTreinos = treinoRep->indexTreinoAluno;
        fprintf(arquivoRelatorio, "%10d  %-42s  %-35s  %-10s  %10s  %10s  \n", aluno->id, aluno->nome, " ", " ", " ", " ");

        while (indTreinos != NULL)
        {
            fseek(fTreinos, indTreinos->posicao * sizeof(Treino), SEEK_SET);
            fread(treino, sizeof(Treino), 1, fTreinos);
            if (!feof(fTreinos)  && treino != NULL)
            {

                if (treino->idAluno == aluno->id)
                {
                    indExercicio = exercicioRep->indexExercicioCodigo;
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

                    fprintf(arquivoRelatorio, "%54s  %-36s  %-10s  %10d  %10.2f  \n","", (exercicio == NULL ? "<EXCLUÍDO>" : exercicio->nome), treino->dataTreino, treino->tempo, (exercicio == NULL ? 0.00 : exercicio->carga));
                }

                indTreinos = indTreinos->proximo;
            }
        }

        indAlunos = indAlunos->proximo;
    }

    liberarPonteiro(exercicio);
    liberarPonteiro(aluno);
    liberarPonteiro(treino);
    fclose(arquivoRelatorio);
    printf("O relatório foi gerado com sucesso!", nomeCaminhoArquivo);

}

/**
 * Este relatório exibe cada exercício, o tempo total de cada exercício, o tempo médio de cada exercício e para cada aluno, o tempo que ele já gastou com o
 * exercício e tempo médio considerando todos os treinos
 */
void relatorioTreinosAgrupadosPorData(AlunoRepositorio * alunoRep, ExercicioRepositorio * exercicioRep, TreinoRepositorio * treinoRep)
{

    char * nomeCaminhoArquivo = lerTexto("Informe o arquivo para impressão do relatório.", 120);
    FILE* arquivoRelatorio = fopen(nomeCaminhoArquivo, "w");
    if (arquivoRelatorio == NULL)
    {
        perror("Não foi possível abrir o arquivo informado.");
        return;
    }

    // Copia os ponteiros dos repositórios para não alterar os originais
    FILE * fExercicios = exercicioRep->exercicioTB;
    FILE * fAlunos = alunoRep->alunoTB;
    FILE * fTreinos = treinoRep->treinoTB;
    IndexAlunoCodigo * indAlunos = alunoRep->indexAlunoCodigo;
    IndexExercicioCodigo * indExercicio = exercicioRep->indexExercicioCodigo;
    IndexTreinoAluno * indTreinos = treinoRep->indexTreinoAluno;

    Exercicio * exercicio = (Exercicio*) malloc(sizeof(Exercicio));
    Aluno * aluno = (Aluno *) malloc(sizeof(Aluno));
    Treino * treino = (Treino *) malloc(sizeof(Treino));
    fprintf(arquivoRelatorio, "%10s  %-42s  %-11s  %-11s  %-35s  %-11s  %-11s\n", "ID", "Exercicio", "Tempo Total", "Tempo Medio", "Aluno", "Tempo Total", "Tempo Medio");
    fprintf(arquivoRelatorio, "%10s  %42s  %11s  %11s  %35s  %11s  %11s\n", "==========", "==========================================", "===========", "===========", "===================================","===========","===========");

    while (indExercicio != NULL)
    {

        fseek(fExercicios, indExercicio->posicao * sizeof(Exercicio), SEEK_SET);
        fread(exercicio, sizeof(Exercicio), 1, fExercicios);

        if (exercicio == NULL || aluno == NULL || treino == NULL)
        {
            perror("Não existe memória disponível para gerar este o relatório solicitado.");
            return;
        }


        if (exercicio->status == 1)
        {
            int qtdEx;
            float tempoExercicioPorAluno;
            float tempoTotalExercicio = 0.00;

            indAlunos = alunoRep->indexAlunoCodigo;
            indTreinos = treinoRep->indexTreinoAluno;

            qtdEx = 0;
            tempoExercicioPorAluno = 0.00;

            while (indTreinos != NULL)
            {
                fseek(fTreinos, indTreinos->posicao * sizeof(Treino), SEEK_SET);
                fread(treino, sizeof(Treino), 1, fTreinos);
                if (!feof(fTreinos)  && treino != NULL)
                {

                    if (treino->idExercicio == exercicio->id)
                    {
                        qtdEx++;
                        tempoTotalExercicio+=treino->tempo;
                    }

                    indTreinos = indTreinos->proximo;
                }
            }
            fprintf(arquivoRelatorio, "\n%10d  %-42s  %11.2f  %11.2f  \n", exercicio->id, exercicio->nome,tempoTotalExercicio, tempoTotalExercicio/qtdEx);

            // Calcula o tempo médio para cada aluno
            indAlunos = alunoRep->indexAlunoCodigo;

            while (indAlunos != NULL)
            {

                fseek(fAlunos, indAlunos->posicao * sizeof(Aluno), SEEK_SET);
                fread(aluno, sizeof(Aluno), 1, fAlunos);
                indTreinos = treinoRep->indexTreinoAluno;

                int qtdExPorAluno = 0;
                float totalExPorAluno = 0.00;

                if (!feof(fAlunos) && aluno != NULL)
                {
                    while (indTreinos != NULL)
                    {
                        fseek(fTreinos, indTreinos->posicao * sizeof(Treino), SEEK_SET);
                        fread(treino, sizeof(Treino), 1, fTreinos);
                        if (!feof(fTreinos)  && treino != NULL)
                        {

                            if (treino->idAluno == aluno->id && treino->idExercicio == exercicio->id)
                            {
                                qtdExPorAluno++;
                                totalExPorAluno+=treino->tempo;
                            }

                            indTreinos = indTreinos->proximo;
                        }
                    }
                    indAlunos = indAlunos->proximo;
                    fprintf(arquivoRelatorio, "\n%10s  %42s  %11s  %11s  %-35s  %11.2f  %11.2f\n", " "," ", " ", " ",aluno->nome, totalExPorAluno, (qtdExPorAluno == 0 ? 0.00 : totalExPorAluno/qtdExPorAluno));
                }
            }

        }

        indExercicio = indExercicio->proximo;
    }

    liberarPonteiro(exercicio);
    liberarPonteiro(aluno);
    liberarPonteiro(treino);
    fclose(arquivoRelatorio);
    printf("O relatório foi gerado com sucesso!", nomeCaminhoArquivo);

}
