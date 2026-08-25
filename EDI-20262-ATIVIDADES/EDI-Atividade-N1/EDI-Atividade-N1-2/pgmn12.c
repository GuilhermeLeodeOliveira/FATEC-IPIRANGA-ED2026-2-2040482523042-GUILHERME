
#include <stdio.h>
#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10
int estoque[TAMANHO_ESTOQUE];

void exibirCabecalho(void){
    
    printf("=================================\n");
    printf("SISTEMA DE ESTOQUE - LOJA CONSTRUMAIS\n");
    printf("=================================\n");
    
}

void preencherEstoque(void){
    int *p = estoque;
    for(int i=0; i<TAMANHO_ESTOQUE; i++){
        printf("Quantidade do produto %d: ", i+1);
        scanf("%d", p+i);
    }
}

void exibirEstoque(int momento){
    int *p = estoque;
    if(momento==0){
        printf("-- Estoque atual (antes da reposicao) --\n");
    }else{
        printf("-- Estoque final (apos reposicao) --\n");
    }
    for(int i=0; i<TAMANHO_ESTOQUE; i++){
        printf("Produto %d: %d unidades\n", i+1, *(p+i));
    }
}

float calcularMediaEstoque(void){
    /*
        p + i    -> endereço do elemento (offset de i inteiros a partir de p)
        *(p + i) -> valor armazenado nesse endereço (conteúdo) 
    */
    int *p = estoque;
    int soma=0;
    for(int i=0; i<TAMANHO_ESTOQUE; i++){
        soma += *(p+i);
    }
    return (float)soma/TAMANHO_ESTOQUE;
}

void simularReposicao(int quantidadeAtual, int reposicao){
    printf("-- Simulacao de reposicao (passagem por valor) --\n");
    printf("Simulacao para o produto 1: %d + %d = %d (nao aplicado ainda)\n", quantidadeAtual, reposicao, quantidadeAtual + reposicao);
}

void aplicarReposicaoGeral(int reposicao){
    int *p = estoque;
    for(int i=0; i<TAMANHO_ESTOQUE; i++){
        *(p+i) += reposicao; // altera diretamente a memória do vetor global
    }
}

void identificarEstoqueCritico(int minimo){
    int *p = estoque;
    int encontrou=0;
    for(int i=0; i<TAMANHO_ESTOQUE; i++){
        if(*(p+i)<minimo){
            printf("Produto %d esta em nivel critico: %d unidades (abaixo do minimo)\n", i + 1, *(p + i));
            encontrou = 1;
            
        }
    }
    if(encontrou == 0){
        printf("Estoque regularizado. Nenhum produto em nivel critico.\n");
    }
}

int main()
{
    
    int reposicao;
    float media;
    
    exibirCabecalho();
    preencherEstoque();
    printf("Quantidade de reposicao a aplicar: ");
    scanf("%d", &reposicao);
    
    exibirEstoque(0);
    
    simularReposicao(estoque[0], reposicao);
    
    printf("Quantidade do produto 1 apos a simulacao (inalterada): %d\n", estoque[0]);

    printf("-- Aplicacao real da reposicao (ponteiro interno ao vetor global) --\n");
    aplicarReposicaoGeral(reposicao);
    printf("Reposicao de %d unidades aplicada a todos os produtos do estoque.\n", reposicao);

    exibirEstoque(1);

    printf("-- Media geral do estoque --\n");
    media = calcularMediaEstoque();
    printf("Media final: %.2f unidades\n", media);

    printf("-- Analise de estoque critico (minimo = %d unidades) --\n", ESTOQUE_MINIMO);
    identificarEstoqueCritico(ESTOQUE_MINIMO);

    return 0;
}