#include <stdio.h>
#define TAMANHO_TURMA 5

void exibirCabecalho(void){
    printf("=================================\n");
    printf(" SISTEMA DE NOTAS - TURMA ADS\n");
    printf("=================================\n");
}

float calcularMedia(float vetor[], int tamanho){
    float soma = 0;
    for(int i=0; i<tamanho; i++){
        soma += vetor[i];
    }
    /*
    OBS: vetor sempre é passado por referência em C porque o nome 
    do vetor decai para o endereço do primeiro elemento (equivale
    a um ponteiro), assim a função acessa a memoria original, não
    uma cópia, e por isso alterações dentro da função refletem
    no vetor da main
    */
    return soma/tamanho;
}

void simularAjuste(float notaOriginal, float bonus){
    float soma = notaOriginal + bonus;
    printf("\n--- Simulacao do ajuste (passagem por valor) ---\n");
    printf("Simulacao para o aluno 1: %.2f + %.2f = %.2f (nao aplicado ainda)\n",
           notaOriginal, bonus, soma);
    printf("Nota do aluno 1 apos a simulacao (inalterada): %.2f\n", notaOriginal);
}

void aplicarBonus(float *nota, float bonus){
    *nota = *nota + bonus;
}

int main()
{
    exibirCabecalho();

    float notas[TAMANHO_TURMA];
    float media, bonus;

    for(int i=0; i<TAMANHO_TURMA; i++){
        printf("Nota do aluno %d: ", i + 1);
        scanf("%f", &notas[i]);
        
    }

    printf("Informe o valor do bonus a aplicar: ");
    scanf("%f", &bonus);

    media = calcularMedia(notas, TAMANHO_TURMA);

    printf("\n--- Media da turma antes do ajuste ---\n");
    printf("Media inicial: %.2f\n", media);

    simularAjuste(notas[0], bonus);

    printf("\n--- Aplicacao real do bonus (passagem por referencia) ---\n");
    for(int i=0; i<TAMANHO_TURMA; i++){
        aplicarBonus(&notas[i], bonus);
    }
    printf("Bonus de %.2f aplicado a todas as notas da turma.\n", bonus);

    printf("\n--- Notas finais da turma ---\n");
    for(int i=0; i<TAMANHO_TURMA; i++){
        printf("Aluno %d: %.2f\n", i+1, notas[i]);
    }

    printf("\n--- Media da turma apos o ajuste ---\n");
    printf("Media final: %.2f\n", calcularMedia(notas, TAMANHO_TURMA));

    return 0;
}