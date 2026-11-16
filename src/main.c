#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "estruturas.h"
#include "entrada.h"
#include "personagens.h"
#include "fases.h"
#include "tabuleiro.h"
#include "eventos.h"
#include "combate.h"
#include "progressao.h"

/* Mostra o titulo e a historia do jogo */
static void exibirIntroducao(void) {

    printf("\n================================\n");
    printf("THE LAST SURVIVORS\n");
    printf("================================\n");
    printf("Um virus devastou o mundo e transformou milhoes em infectados.\n");
    printf("Voce e um dos ultimos sobreviventes e precisa atravessar a cidade,\n");
    printf("o hospital e a base militar para encontrar a cura.\n");
}

/* Mostra o status do jogador no inicio de cada rodada */
static void exibirStatus(const Jogo *jogo) {

    printf("\n--- FASE %d: %s ---\n", jogo->faseAtual + 1,
           jogo->fases[jogo->faseAtual].nome);
    printf("%s | Nivel %d | XP %d/%d\n", jogo->jogador.nome,
           jogo->jogador.nivel, jogo->jogador.experiencia,
           jogo->jogador.nivel * 100);
    mostrarPersonagem(&jogo->jogador);
}

/* Uma rodada no tabuleiro: mostrar, mover, evento, combate e verificacoes */
static void executarRodada(Jogo *jogo) {

    exibirStatus(jogo);
    exibirTabuleiro(&jogo->fases[jogo->faseAtual], jogo->posicao);

    aguardarEnter("\nPressione ENTER para jogar o dado...");

    moverJogador(&jogo->posicao);
    executarEvento(jogo);

    if (jogo->jogoFinalizado == 1) {
        return;
    }

    if (jogo->emCombate == 1) {
        iniciarCombate(jogo);

        /* Fugir do chefe faz o jogador recuar no tabuleiro */
        if (jogo->fugiu == 1 && jogo->combateChefe == 1) {
            jogo->posicao = TOTAL_CASAS - 4;
            printf("Voce recuou para a casa %d.\n", jogo->posicao);
        }
    }

    if (jogo->jogoFinalizado == 1) {
        return;
    }

    verificarAvancoFase(jogo);
}

/* Mostra o resultado final */
static void exibirResultadoFinal(const Jogo *jogo) {

    printf("\n================================\n");

    if (jogo->venceu == 1) {
        printf("PARABENS! VOCE ENCONTROU A CURA!\n");
        printf("VOCE SALVOU A HUMANIDADE!\n");
    } else {
        printf("GAME OVER! VOCE FOI DERROTADO!\n");
    }

    printf("================================\n");
    printf("Resumo do heroi: %s - nivel %d\n", jogo->jogador.nome, jogo->jogador.nivel);
    mostrarPersonagem(&jogo->jogador);
}

int main(void) {

    srand((unsigned int) time(NULL));

    Jogo jogo = {0};
    Personagem personagens[TOTAL_PERSONAGENS];

    exibirIntroducao();

    carregarPersonagens(personagens);
    escolherPersonagem(personagens, &jogo.jogador);

    carregarFases(jogo.fases);
    prepararTabuleiro(jogo.fases);

    jogo.faseAtual = 0;
    jogo.posicao = 1;

    apresentarFase(&jogo.fases[0], 1);

    while (jogo.jogoFinalizado == 0) {
        executarRodada(&jogo);
    }

    exibirResultadoFinal(&jogo);

    return 0;
}
