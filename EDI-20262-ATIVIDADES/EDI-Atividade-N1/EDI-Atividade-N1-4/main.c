/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
 * Disciplina : Estrutura de Dados                                                                                  *
 *                    Prof . Verissimo                                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
 * Data - 14 / 09 / 2026                                                                                            *
 * Autor : [Guilherme Leo de Oliveira]                                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    int id;
    char nome[50];
    struct no *prox;
} No;

typedef No *NoPtr;

typedef struct
{
    NoPtr ini;
    NoPtr fim;
} Cabecalho;

typedef Cabecalho *Fila;

/* Criacao da fila */
Fila Criar()
{
    Fila f = (Fila)malloc(sizeof(Cabecalho));
    if (f != NULL)
    {
        f->ini = NULL;
        f->fim = NULL;
    }
    return f;
}

/* Insercao no fim da fila (enqueue) */
int inserir(Fila f, int id, const char *nome)
{
    NoPtr novo = (NoPtr)malloc(sizeof(No));
    if (novo == NULL)
        return 0;
    novo->id = id;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->prox = NULL;

    if (f->ini == NULL)
        f->ini = novo;
    else
        f->fim->prox = novo;

    f->fim = novo;
    return 1;
}

/* Listagem da fila */
void listarFila(Fila f)
{
    if (f == NULL || f->ini == NULL)
    {
        printf("\n[ AVISO ] A fila esta vazia.\n");
        return;
    }
    NoPtr atual = f->ini;
    printf("\n=== FILA DE PACIENTES ===\n");
    while (atual != NULL)
    {
        printf("ID: %d - Nome : %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("=========================\n");
}

/* Atendimento do Paciente (Remocao / Desenfileirar / dequeue) */
int atenderPaciente(Fila f)
{
    if (f == NULL || f->ini == NULL)
    {
        printf("\n[ AVISO ] A fila esta vazia.\n");
        return 0;
    }
    NoPtr removido = f->ini;
    printf("\n>> Atendendo paciente: ID: %d - Nome: %s\n", removido->id, removido->nome);
    f->ini = removido->prox;      /* o segundo no passa a ser o inicio */
    if (f->ini == NULL)           /* se a fila esvaziou, ajusta o fim */
        f->fim = NULL;
    free(removido);               /* libera a memoria do no removido */
    return 1;
}

/* Consulta do Proximo Paciente (Primeiro / peek) */
void consultarProximo(Fila f)
{
    if (f == NULL || f->ini == NULL)
    {
        printf("\n[ AVISO ] A fila esta vazia.\n");
        return;
    }
    printf("\n>> Proximo paciente da fila: ID: %d - Nome: %s\n",
           f->ini->id, f->ini->nome);
}

/* Tamanho da Fila / Contagem */
int tamanhoFila(Fila f)
{
    if (f == NULL)
        return 0;
    int cont = 0;
    NoPtr atual = f->ini;
    while (atual != NULL)
    {
        cont++;
        atual = atual->prox;
    }
    return cont;
}

/* Verificacao de Fila Vazia */
int filaVazia(Fila f)
{
    return (f == NULL || f->ini == NULL);
}

/* Esvaziar a Fila (libera todos os nos, mantendo o cabecalho utilizavel) */
void esvaziarFila(Fila f)
{
    if (f == NULL)
        return;
    NoPtr atual = f->ini;
    while (atual != NULL)
    {
        NoPtr aux = atual;   /* guarda o no atual */
        atual = atual->prox; /* avanca antes de liberar */
        free(aux);
    }
    f->ini = NULL;
    f->fim = NULL;
    printf("\n>> Fila esvaziada. Todos os nos foram desalocados.\n");
}

/* Destruir a Fila (esvazia e libera tambem o cabecalho) */
void destruirFila(Fila f)
{
    if (f == NULL)
        return;
    esvaziarFila(f);
    free(f);
}

int main()
{
    Fila filaAtendimento = Criar();
    int opcao, id;
    char nome[50];

    do
    {
        printf("\n- - - SISTEMA HOSPITALAR ( FATEC IPIRANGA ) - - -\n");
        printf("1. Chegada de Paciente ( Inserir na Fila )\n");
        printf("2. Listar Fila de Pacientes\n");
        printf("3. Atendimento do Paciente\n");
        printf("4. Consulta do Proximo Paciente\n");
        printf("5. Tamanho da Fila / Contagem\n");
        printf("6. Verificacao de Fila Vazia\n");
        printf("7. Esvaziar / Desalocar a Fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Informe o ID do paciente: ");
            scanf("%d", &id);
            getchar(); // Limpar buffer do teclado
            printf("Informe o Nome do paciente: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0; // Remover quebra de linha
            if (inserir(filaAtendimento, id, nome))
                printf(">> Paciente inserido com sucesso!\n");
            else
                printf(">> Erro ao inserir paciente.\n");
            break;

        case 2:
            listarFila(filaAtendimento);
            break;

        case 3:
            if (atenderPaciente(filaAtendimento))
                printf(">> Paciente removido da fila com sucesso.\n");
            break;

        case 4:
            consultarProximo(filaAtendimento);
            break;

        case 5:
            printf("\n>> Tamanho da fila: %d paciente(s) aguardando atendimento.\n",
                   tamanhoFila(filaAtendimento));
            break;

        case 6:
            if (filaVazia(filaAtendimento))
                printf("\n>> A fila esta VAZIA.\n");
            else
                printf("\n>> A fila NAO esta vazia.\n");
            break;

        case 7:
            esvaziarFila(filaAtendimento);
            break;

        case 0:
            printf("Encerrando o sistema...\n");
            destruirFila(filaAtendimento); // Libera todos os nos e o cabecalho
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}