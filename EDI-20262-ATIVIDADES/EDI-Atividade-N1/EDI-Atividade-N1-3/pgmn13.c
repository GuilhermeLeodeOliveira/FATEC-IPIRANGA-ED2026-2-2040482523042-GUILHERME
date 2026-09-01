/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
 * Disciplina : Estrutura de Dados                                                                                  *
 *                    Prof . Verissimo                                                                               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
 * Objetivo do Programa : Sistema de atendimento do Lava-Rapido Brilho Total, utilizando alocacao dinamica (malloc) *
 *                        para armazenar a frota do dia e funcoes recursivas para exibicao, soma, busca e contagem. *
 * Data - 01 / 09 / 2026                                                                                            *
 * Autor : [Guilherme Leo de Oliveira]                                                                                 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_PREMIUM 100.0

typedef struct {
    char placa[8];
    float valor;
} Veiculo;

void exibirCabecalho(void) {
    printf("=================================\n");
    printf(" LAVA - RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n");
    printf(" =================================\n");
}

void preencherFrota(Veiculo *frota, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Placa do veiculo %d: ", i + 1);
        scanf("%7s", (frota + i)->placa);
        printf("Valor do servico (R$): ");
        scanf("%f", &(frota + i)->valor);
    }
}

void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) {
        return; 
    }
    printf("%d) Placa: %s | Valor: R$ %.2f\n",
           indice + 1, frota[indice].placa, frota[indice].valor);
    exibirFrotaRecursivo(frota, indice + 1, quantidade); 
}

float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) {
        return 0.0f; 
    }
    return frota[indice].valor +
           calcularValorTotalRecursivo(frota, indice + 1, quantidade); 
}


int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]) {
    if (indice == quantidade) {
        return -1;
    }
    if (strcmp(frota[indice].placa, placa) == 0) {
        return indice;
    }
    return buscarVeiculoRecursivo(frota, indice + 1, quantidade, placa);
}


int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) {
        return 0;
    }
    int count = contarPremiumRecursivo(frota, indice + 1, quantidade); 
    if (frota[indice].valor >= VALOR_PREMIUM) {
        return 1 + count;
    }
    return count;
}

int main(void) {
    exibirCabecalho();

    int quantidade;
    printf("Quantos veiculos serao atendidos hoje? ");
    scanf("%d", &quantidade);

    Veiculo *frota = (Veiculo *)malloc(quantidade * sizeof(Veiculo));
    if (frota == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    preencherFrota(frota, quantidade);

    printf("\n--- Veiculos atendidos hoje ---\n");
    exibirFrotaRecursivo(frota, 0, quantidade);

    printf("\n--- Busca recursiva por placa ---\n");
    char placaBusca[8];
    printf("Placa a ser pesquisada: ");
    scanf("%7s", placaBusca);

    int posicao = buscarVeiculoRecursivo(frota, 0, quantidade, placaBusca);
    if (posicao != -1) {
        printf("Veiculo encontrado na posicao %d! Placa: %s | Valor: R$ %.2f\n",
               posicao + 1, frota[posicao].placa, frota[posicao].valor);
    } else {
        printf("Veiculo nao encontrado na frota.\n");
    }

    printf("\n--- Resumo do dia ---\n");
    printf("Total de veiculos atendidos: %d\n", quantidade);
    printf("Servicos premium (>= R$ 100.00): %d\n",
           contarPremiumRecursivo(frota, 0, quantidade));
    printf("Valor total arrecadado: R$ %.2f\n",
           calcularValorTotalRecursivo(frota, 0, quantidade));

    free(frota);
    frota = NULL;
    printf("\nMemoria da frota liberada com sucesso. Sistema encerrado.");

    return 0;
}