#include <stdio.h>
#include <stdlib.h>

#include "Constantes.h"
#include "IndexAlunoCodigo.h"
#include "IndexExercicioNome.h"
#include "IndexExercicioCodigo.h"
#include "IndexTreinoAluno.h"
#include "Alunos.h"
#include "Aluno.h"
#include "Treino.h"
#include "Alunos.c"
#include "Treinos.c"
#include "Exercicios.h"
#include "Exercicios.c"
#include "Exercicio.h"
#include "Utils.c"

#include "AlunoRepositorio.h"
#include "ExercicioRepositorio.h"
#include "TreinoRepositorio.h"
#include "AlunoRepositorioImpl.c"
#include "TreinoRepositorioImpl.c"
#include "ExercicioRepositorioImpl.c"

FILE* abrirTabelaAlunos();

FILE* abrirTabelaExercicios();

FILE* abrirTabelaTreinos();

void fecharTabela(FILE * arquivo);

void* liberarPonteiro(void* ponteiro);

void pressionarTeclaContinuar();

int main()
{
    FILE * dados = abrirTabelaAlunos();
    FILE * dadosExercicios = abrirTabelaExercicios();
    FILE * dadosTreinos = abrirTabelaTreinos();
    IndexAlunoCodigo * listaAlunos = carregarIndiceCodigo(NOME_INDEX_TB_ALUNO_CODIGO);
    IndexAlunoCPF * listaAlunosIndexadosPorCPF = carregarIndiceCPF(NOME_INDEX_TB_ALUNO_CPF);
    IndexExercicioNome * listaExerciciosIndexadosPorNome = carregarIndiceNomeExercicio(NOME_INDEX_TB_EXERCICIO_NOME);
    IndexExercicioCodigo * listaExerciciosIndexadosPorCodigo = carregarIndiceCodigoExercicio(NOME_INDEX_TB_EXERCICIO_CODIGO);
    IndexTreinoAluno * listaTreinosIndexadosPorAluno = carregarIndiceTreinoAluno(NOME_INDEX_TB_TREINO_ALUNO);

    // Variáveis dos cadastros
    Aluno* aluno;
    Exercicio * exercicio;
    Treino * treino;
    // Variáveis dos indices
    int posicaoAluno;
    int posicaoExercicio;
    int posicaoTreino;
    // Variáveis do menu
    int opcao;
    do
    {
        opcao = menuTipoUsuario();

        switch(opcao)
        {

        case 1:
        {
            int opcaoNivel2;
            do
            {
                opcaoNivel2 = menuAluno();

                switch(opcaoNivel2)
                {

                case 2:
                {
                    // Consulta um aluno, simulação de autenticação, sem senha...
                    int idAluno = lerInteiro("Informe a sua matrícula...\n");
                    Aluno* aluno = buscarPorCodigo(dados, listaAlunos, idAluno);
                    getchar();
                    if (aluno == NULL)
                    {
                        printf("Nenhum usuário encontrado com a Matrícula informada \"%d\"\n", idAluno);
                        break;
                    }
                    // Consulta o exercício, simulando preenchimento ou selecionar uma opção disponível
                    int idExercicio = lerInteiro("Informe o exercício...\n");
                    Exercicio* exercicio = buscarPorCodigoExercicio(dadosExercicios, listaExerciciosIndexadosPorCodigo, idExercicio);
                    getchar();
                    if (exercicio == NULL)
                    {
                        printf("Nenhum exercício encontrado com o código informado \"%d\"\n", idExercicio);
                        break;
                    }

                    //`Passando objetos já populados para não propagar lógica de consulta destas entidades...
                    treino = treinar(aluno, exercicio);
                    posicaoTreino = escreverTreino(dadosTreinos, treino);
                    listaTreinosIndexadosPorAluno = adicionarIndexTreinoAluno(listaTreinosIndexadosPorAluno, treino->id, posicaoTreino);
                    printf("\nTreino lançado com sucesso!\n");
                    pressionarTeclaContinuar();
                    break;
                }
                case 3:
                {
                    AlunoRepositorio * alunoRepo = criarAlunoRepositorio(listaAlunos, dados);
                    TreinoRepositorio * treinoRepo = criarTreinoRepositorio(listaTreinosIndexadosPorAluno, dadosTreinos);
                    ExercicioRepositorio * exercicioRepo = criarAlunoRepositorio(listaExerciciosIndexadosPorCodigo, dadosExercicios);
                    listarTodosTreinos(alunoRepo, exercicioRepo, treinoRepo);
                    pressionarTeclaContinuar();
                    break;
                }


                }

            }
            while (opcaoNivel2 != 0 && opcaoNivel2 != 1);
            if (opcaoNivel2 == 0)
                opcao = 0;

            break;
        }
        case 2:
        {

            int opcaoNivel3;
            do
            {
                opcaoNivel3 = menuAdministrador();

                switch(opcaoNivel3)
                {

                case 1:
                {
                    // Retorna par o menu anterior
                    break;
                }
                case 2:
                {
                    aluno = criarAluno();

                    Aluno* alunoCon = buscarPorCodigo(dados, listaAlunos, aluno->id);

                    if (alunoCon != NULL)
                    {
                        printf("Já existe um aluno com o código informado \"%d\"\n", alunoCon->id);
                        getchar();
                        break;
                    }


                    alunoCon = buscarPorCPF(dados, listaAlunosIndexadosPorCPF, aluno->cpf);
                    if (alunoCon != NULL)
                    {
                        printf("Já existe um aluno com o CPF informado \"%s\"\n", alunoCon->cpf);
                        getchar();
                        break;
                    }

                    posicaoAluno = escreverAluno(dados, aluno);
                    listaAlunos = adicionarIndexCodigo(listaAlunos, aluno->id, posicaoAluno);
                    listaAlunosIndexadosPorCPF = adicionarIndexCPF(listaAlunosIndexadosPorCPF, aluno->cpf, posicaoAluno);
                    aluno = (Aluno*) liberarPonteiro(aluno);
                    printf("Aluno cadastrado com sucesso!\n");
                    pressionarTeclaContinuar();
                    break;
                }

                case 3:
                {
                    int codigo = lerInteiro("Informe a matrícula/código para editar...\n");
                    Aluno* aluno = buscarPorCodigo(dados, listaAlunos, codigo);
                    getchar();
                    if (aluno == NULL)
                    {
                        printf("Nenhum aluno encontrado com a Matrícula informada \"%d\"\n", codigo);
                    }
                    else
                    {
                        printf("\nEditar aluno: \n");
                        char * cpfAntigo = malloc(15*sizeof(char));
                        cpfAntigo = aluno->cpf;
                        editarAluno(aluno);
                        posicaoAluno = atualizarAluno(dados, aluno);
                        removerIndexCPF(listaAlunosIndexadosPorCPF, cpfAntigo);
                        listaAlunosIndexadosPorCPF = adicionarIndexCPF(listaAlunosIndexadosPorCPF, aluno->cpf, posicaoAluno);
                        printf("\Alterações salvas com sucesso!\n");

                    }
                    pressionarTeclaContinuar();
                    break;
                }

                case 4:
                {
                    int codigo = lerInteiro("Informe a matrícula/código para excluir...\n");
                    Aluno* aluno = buscarPorCodigo(dados, listaAlunos, codigo);
                    getchar();
                    if (aluno == NULL)
                    {
                        printf("Nenhum aluno encontrado com a Matrícula informada \"%d\"\n", codigo);
                    }
                    else
                    {
                        printf("\nExcluindo aluno...\n");
                        excluirAluno(dados, aluno->id);
                        listaAlunos = removerIndexCodigo(listaAlunos, aluno->id);
                        listaAlunosIndexadosPorCPF = removerIndexCPF(listaAlunosIndexadosPorCPF, aluno->cpf);
                        printf("\nAluno excluído com sucesso!\n");
                    }
                    pressionarTeclaContinuar();
                    break;
                }


                case 5:
                {
                    int codigo = lerInteiro("Informe a matrícula/código para consulta...\n");
                    Aluno* aluno = buscarPorCodigo(dados, listaAlunos, codigo);
                    getchar();
                    if (aluno == NULL)
                    {
                        printf("Nenhum aluno encontrado com a Matrícula informada \"%d\"\n", codigo);
                    }
                    else
                    {
                        printf("\nAluno encontrado: \n");
                        imprimirAluno(aluno);
                        aluno = (Aluno*) liberarPonteiro(aluno);
                    }
                    pressionarTeclaContinuar();
                    break;
                }

                case 6:
                {
                    char * cpf = lerTexto("Informe o CPF para consulta...\n", 15);
                    Aluno* aluno = buscarPorCPF(dados, listaAlunosIndexadosPorCPF, cpf);
                    if (aluno == NULL)
                    {
                        printf("Nenhum aluno encontrado com o CPF informado \"%s\"\n", cpf);
                    }
                    else
                    {
                        printf("\nAluno encontrado: \n");
                        imprimirAluno(aluno);
                        aluno = (Aluno*) liberarPonteiro(aluno);
                    }
                    pressionarTeclaContinuar();
                    break;
                }

                case 7:
                {
                    listarTodos(dados, listaAlunos);
                    pressionarTeclaContinuar();
                    break;
                }

                case 8:
                {
                    listarTodosAlunosAtivos(dados, listaAlunos);
                    pressionarTeclaContinuar();
                    break;
                }

                case 9:
                {
                    exercicio = criarExercicio();
                    posicaoExercicio = escreverExercicio(dadosExercicios, exercicio);
                    listaExerciciosIndexadosPorCodigo = adicionarIndexCodigo(listaExerciciosIndexadosPorCodigo, exercicio->id, posicaoExercicio);
                    listaExerciciosIndexadosPorNome = adicionarIndexExercicioNome(listaExerciciosIndexadosPorNome, exercicio->nome, posicaoExercicio);
                    exercicio = (Exercicio*) liberarPonteiro(exercicio);
                    printf("Exercício cadastrado com sucesso!\n");
                    pressionarTeclaContinuar();
                    break;
                }

                case 10:
                {
                    int codigoEx = lerInteiro("Informe a código para editar...\n");
                    Exercicio* exercicio = buscarPorCodigoExercicio(dadosExercicios, listaExerciciosIndexadosPorCodigo, codigoEx);
                    getchar();
                    if (exercicio == NULL)
                    {
                        printf("Nenhum exercício encontrado com o código informado \"%d\"\n", codigoEx);
                    }
                    else
                    {
                        printf("\nEditar exercício: \n");
                        char * nomeAntigo = malloc(120*sizeof(char));
                        nomeAntigo = exercicio->nome;
                        editarExercicio(exercicio);
                        posicaoExercicio = atualizarExercicio(dadosExercicios, exercicio);
                        // listaExerciciosIndexadosPorCodigo = adicionarIndexCodigoExercicio(listaExerciciosIndexadosPorCodigo, exercicio->id, posicaoExercicio);
                        removerIndexExercicioNome(listaExerciciosIndexadosPorNome, nomeAntigo);
                        listaExerciciosIndexadosPorNome = adicionarIndexExercicioNome(listaExerciciosIndexadosPorNome, exercicio->nome, posicaoExercicio);
                        printf("\Alterações salvas com sucesso!\n");

                    }
                    pressionarTeclaContinuar();
                    break;
                }

                case 11:
                {
                    int codigoEx = lerInteiro("Informe a código para excluir...\n");
                    Exercicio* exercicio = buscarPorCodigoExercicio(dadosExercicios, listaExerciciosIndexadosPorCodigo, codigoEx);
                    getchar();
                    if (exercicio == NULL)
                    {
                        printf("Nenhum exercício encontrado com o código informado \"%d\"\n", codigoEx);
                    }
                    else
                    {
                        printf("\nExcluindo exercício...\n");
                        excluirExercicio(dadosExercicios, exercicio->id);
                        listaExerciciosIndexadosPorCodigo = removerIndexExercicioCodigo(listaExerciciosIndexadosPorCodigo, exercicio->id);
                        listaExerciciosIndexadosPorNome = removerIndexExercicioNome(listaExerciciosIndexadosPorNome, exercicio->nome);
                        printf("\nExercício excluído com sucesso!\n");
                    }
                    pressionarTeclaContinuar();
                    break;
                }

                case 12:
                {
                    int codigoEx = lerInteiro("Informe o código para consultar...\n");
                    Exercicio* exercicio = buscarPorCodigoExercicio(dadosExercicios, listaExerciciosIndexadosPorCodigo, codigoEx);
                    getchar();
                    if (exercicio == NULL)
                    {
                        printf("Nenhum exercício encontrado com o código informado \"%d\"\n", codigoEx);
                    }
                    else
                    {
                        printf("\nCódigo encontrado: \n");
                        imprimirExercicio(exercicio);
                        exercicio = (Exercicio*) liberarPonteiro(exercicio);
                    }
                    pressionarTeclaContinuar();
                    break;
                }

                case 13:
                {
                    char * nome = lerTexto("Informe o NOME para consulta...\n", 20);
                    Exercicio* exercicio = buscarPorNomeExercicio(dadosExercicios, listaExerciciosIndexadosPorNome, nome);
                    if (exercicio == NULL)
                    {
                        printf("Nenhum aluno encontrado com o NOME informado \"%s\"\n", nome);
                    }
                    else
                    {
                        printf("\nExercício encontrado: \n");
                        imprimirExercicio(exercicio);
                        exercicio = (Exercicio*) liberarPonteiro(exercicio);
                    }
                    pressionarTeclaContinuar();
                    break;
                }
                case 14:
                {
                    listarTodosExercicios(dadosExercicios, listaExerciciosIndexadosPorCodigo);
                    pressionarTeclaContinuar();
                    break;
                }

                case 15:
                {
                    listarTodosExerciciosAtivos(dadosExercicios, listaExerciciosIndexadosPorCodigo);
                    pressionarTeclaContinuar();
                    break;
                }

                case 16:
                {

                    AlunoRepositorio * alunoRepo = criarAlunoRepositorio(listaAlunos, dados);
                    TreinoRepositorio * treinoRepo = criarTreinoRepositorio(listaTreinosIndexadosPorAluno, dadosTreinos);
                    ExercicioRepositorio * exercicioRepo = criarAlunoRepositorio(listaExerciciosIndexadosPorCodigo, dadosExercicios);
                    relatorioAlunosAgrupadosPorExercicio(alunoRepo, exercicioRepo, treinoRepo);
                    pressionarTeclaContinuar();
                    break;
                }

                case 17:
                {

                    AlunoRepositorio * alunoRepo = criarAlunoRepositorio(listaAlunos, dados);
                    TreinoRepositorio * treinoRepo = criarTreinoRepositorio(listaTreinosIndexadosPorAluno, dadosTreinos);
                    ExercicioRepositorio * exercicioRepo = criarAlunoRepositorio(listaExerciciosIndexadosPorCodigo, dadosExercicios);
                    relatorioTreinosAgrupadosPorAluno(alunoRepo, exercicioRepo, treinoRepo);
                    pressionarTeclaContinuar();
                    break;
                }

                case 18:
                {

                    AlunoRepositorio * alunoRepo = criarAlunoRepositorio(listaAlunos, dados);
                    TreinoRepositorio * treinoRepo = criarTreinoRepositorio(listaTreinosIndexadosPorAluno, dadosTreinos);
                    ExercicioRepositorio * exercicioRepo = criarAlunoRepositorio(listaExerciciosIndexadosPorCodigo, dadosExercicios);
                    relatorioTreinosAgrupadosPorData(alunoRepo, exercicioRepo, treinoRepo);
                    pressionarTeclaContinuar();
                    break;
                }

                }

            }
            while (opcaoNivel3 != 0 && opcaoNivel3 != 1);
            if (opcaoNivel3 == 0)
                opcao = 0;

            break;
        }

        }

    }
    while (opcao != 0);
    system("clear");
    printf("\n\n Fechando conexão e persistindo dados");
    fecharTabela(dados);
    fecharTabela(dadosExercicios);
    printf(" - OK \n");
    printf(" Atualizando índices");
    escreverIndiceCodigo(listaAlunos, NOME_INDEX_TB_ALUNO_CODIGO);
    escreverIndiceCPF(listaAlunosIndexadosPorCPF, NOME_INDEX_TB_ALUNO_CPF);
    escreverIndiceCodigoExercicio(listaExerciciosIndexadosPorCodigo, NOME_INDEX_TB_EXERCICIO_CODIGO);
    escreverIndiceNomeExercicio(listaExerciciosIndexadosPorNome, NOME_INDEX_TB_EXERCICIO_NOME);
    escreverIndiceTreino(listaTreinosIndexadosPorAluno, NOME_INDEX_TB_TREINO_ALUNO);
    printf(" - OK \n");
    printf("\n Programa finalizado com sucesso. \n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}

int menuTipoUsuario()
{
    int opcao;
    do
    {
        system("clear");
        printf("==========================\n");
        printf("======= FatBodyGym =======\n");
        printf("========== MENU ==========\n");
        printf("==========================\n");
        printf(" 0. X - Sair\n");
        printf("==========================\n");
        printf(" Eu sou?\n");
        printf(" 1. Aluno\n");
        printf(" 2. Administrador\n");
        printf("==========================\n");
        printf(" Digite uma opção: ");
        scanf("%d%*c", &opcao);
        if (opcao < 0 || opcao > 5)
        {
            printf("Opção inválida!");
            scanf("%*c");
        }
    }
    while (opcao < 0 || opcao > 5);
    system("clear");
    return opcao;
}

int menuAluno()
{
    int opcao;
    do
    {
        system("clear");
        printf("==========================\n");
        printf("======= FatBodyGym =======\n");
        printf("======= MENU ALUNO =======\n");
        printf("==========================\n");
        printf(" 0. X - Sair\n");
        printf(" 1. <-- Voltar\n");
        printf("==========================\n");
        printf(" 2. Lançar um treino\n");
        printf(" 3. Listar treinos\n");
        printf("==========================\n");
        printf(" Escolha uma opção: ");
        scanf("%d%*c", &opcao);
        if (opcao < 0 || opcao > 5)
        {
            printf("Opção inválida!");
            scanf("%*c");
        }
    }
    while (opcao < 0 || opcao > 5);
    system("clear");
    return opcao;

}

int menuAdministrador()
{
    int opcao;
    do
    {
        system("clear");
        printf("==========================\n");
        printf("======= FatBodyGym =======\n");
        printf("=== MENU ADMINISTRADOR ===\n");
        printf("==========================\n");
        printf(" 0. X - Sair\n");
        printf(" 1. <-- Voltar\n");
        printf("==========================\n");
        printf(" 2. Cadastrar Aluno\n");
        printf(" 3. Editar Aluno\n");
        printf(" 4. Excluir Aluno\n");
        printf(" 5. Buscar Aluno por Matrícula\n");
        printf(" 6. Buscar Aluno por CPF\n");
        printf(" 7. Listar todos os alunos\n");
        printf(" 8. Listar todos os alunos ativos\n");
        printf(" 9. Cadastrar Exercício\n");
        printf("10. Editar Exercício\n");
        printf("11. Excluir Exercício\n");
        printf("12. Buscar Exercício por código\n");
        printf("13. Buscar Exercício por nome\n");
        printf("14. Listar todos os Exercícios\n");
        printf("15. Listar todos os Exercícios ativos\n");
        printf("============================\n");
        printf(" RELATÓRIOS PARA ARQUIVO \n");
        printf("============================\n");
        printf("16. Alunos agrupados por exercício\n");
        printf("17. Treinos agrupados por alunos\n");
        printf("18. Estatísticas dos exercícios X Alunos\n");
        printf("============================\n");
        printf(" Escolha uma opção: ");
        scanf("%d%*c", &opcao);
        if (opcao < 0 || opcao > 18)
        {
            printf("Opção inválida!");
            scanf("%*c");
        }
    }
    while (opcao < 0 || opcao > 18);
    system("clear");
    return opcao;

}

FILE* abrirTabelaAlunos()
{
    // Tenta ler o arquivo
    FILE *arquivo = fopen(NOME_TB_ALUNOS, "rb+");
    if (arquivo == NULL)
    {
        // Se não foi possível ler, cria o banco
        arquivo = fopen(NOME_TB_ALUNOS, "wb+");
        if (arquivo == NULL)
        {
            perror("Não foi possível criar tabela alunos.");
            exit(1);
        }
    }
    return arquivo;
}

FILE* abrirTabelaExercicios()
{
    // Tenta ler o arquivo
    FILE *arquivo = fopen(NOME_TB_EXERCICIOS, "rb+");
    if (arquivo == NULL)
    {
        // Se não foi possível ler, cria o banco
        arquivo = fopen(NOME_TB_EXERCICIOS, "wb+");
        if (arquivo == NULL)
        {
            perror("Não foi possível criar tabela exercícios.");
            exit(1);
        }
    }
    return arquivo;
}

FILE* abrirTabelaTreinos()
{
    // Tenta ler o arquivo
    FILE *arquivo = fopen(NOME_TB_TREINOS, "rb+");
    if (arquivo == NULL)
    {
        // Se não foi possível ler, cria o banco
        arquivo = fopen(NOME_TB_TREINOS, "wb+");
        if (arquivo == NULL)
        {
            perror("Não foi possível criar tabela treinos.");
            exit(1);
        }
    }
    return arquivo;
}

void fecharTabela(FILE * arquivo)
{
    if (fclose(arquivo) != 0)
    {
        perror("Ocorreu um erro ao fechar tabela.");
        exit(1);
    }
}

void pressionarTeclaContinuar()
{
    printf("\n\nPressione uma tecla para continuar...");
    getchar();
}
