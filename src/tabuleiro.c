#include <stdio.h>
#include <stdlib.h>

#include "estruturas.h"
#include "tabuleiro.h"

/* Distribui os tipos de casas em cada fase (a ultima casa e sempre a missao) */
void prepararTabuleiro(Fase fases[]) {

    TipoCasa distribuicao[TOTAL_FASES][TOTAL_CASAS] = {
        /* Fase 1 */
        { CASA_VAZIA, CASA_COMBATE, CASA_TESOURO, CASA_VAZIA,
          CASA_CURA, CASA_COMBATE, CASA_ARMADILHA, CASA_TESOURO,
          CASA_VAZIA, CASA_CURA, CASA_COMBATE, CASA_MISSAO },
        /* Fase 2 */
        { CASA_VAZIA, CASA_COMBATE, CASA_CURA, CASA_COMBATE,
          CASA_TESOURO, CASA_ARMADILHA, CASA_COMBATE, CASA_CURA,
          CASA_TESOURO, CASA_COMBATE, CASA_CURA, CASA_MISSAO },
        /* Fase 3 */
        { CASA_VAZIA, CASA_COMBATE, CASA_CURA, CASA_COMBATE,
          CASA_TESOURO, CASA_COMBATE, CASA_CURA, CASA_ARMADILHA,
          CASA_COMBATE, CASA_CURA, CASA_TESOURO, CASA_MISSAO }
    };

    for (int i = 0; i < TOTAL_FASES; i++) {
        for (int j = 0; j < TOTAL_CASAS; j++) {
            fases[i].casas[j] = distribuicao[i][j];
        }
    }
}

/* Sorteia um numero de 1 ate o numero de lados do dado */
int rolarDado(int lados) {
    return (rand() % lados) + 1;
}

/* Movimenta o jogador pelo tabuleiro (altera a posicao por ponteiro) */
void moverJogador(int *posicao) {

    int resultado = rolarDado(6);

    printf("\nVoce tirou %d no dado!\n", resultado);

    *posicao = *posicao + resultado;

    /* Impede que o jogador ultrapasse a ultima casa */
    if (*posicao > TOTAL_CASAS) {
        *posicao = TOTAL_CASAS;
    }

    /* Impede que o jogador fique antes da primeira casa */
    if (*posicao < 1) {
        *posicao = 1;
    }

    printf("Voce esta na casa %d.\n", *posicao);
}

static const char *nomeCasa(TipoCasa tipo) {

    switch (tipo) {
        case CASA_VAZIA:    return "Vazia";
        case CASA_COMBATE:  return "Combate";
        case CASA_TESOURO:  return "Tesouro";
        case CASA_CURA:     return "Cura";
        case CASA_ARMADILHA:return "Armadilha";
        case CASA_MISSAO:   return "Missao / Chefe";
    }

    return "?";
}

/* Exibe as casas do tabuleiro */
void exibirTabuleiro(const Fase *fase, int posicao) {

    printf("\n========== TABULEIRO ==========\n");

    for (int i = 0; i < TOTAL_CASAS; i++) {

        printf("Casa %02d: %-15s", i + 1, nomeCasa(fase->casas[i]));

        if (i + 1 == posicao) {
            printf(" <== VOCE");
        }

        printf("\n");
    }

    printf("===============================\n");
}
