#include <stdio.h>
#include <stdlib.h>

#include "estruturas.h"
#include "eventos.h"
#include "personagens.h"
#include "monstros.h"
#include "progressao.h"

/* Executa o evento da casa em que o jogador parou */
void executarEvento(Jogo *jogo) {

    Fase *fase = &jogo->fases[jogo->faseAtual];
    Personagem *heroi = &jogo->jogador;
    TipoCasa casa = fase->casas[jogo->posicao - 1];

    printf("\n===== EVENTO DA CASA =====\n");

    switch (casa) {

        case CASA_VAZIA:
            printf("Voce encontrou uma area vazia. Nada aconteceu.\n");
            break;

        case CASA_COMBATE: {
            /* Sorteia um dos monstros comuns da fase (o chefe fica na casa final) */
            int sorteio = rand() % (TOTAL_MONSTROS - 1);

            jogo->monstroAtual = fase->monstros[sorteio];
            jogo->emCombate = 1;
            jogo->combateChefe = 0;

            printf("UM INFECTADO APARECEU!\n");
            mostrarMonstro(&jogo->monstroAtual);
            break;
        }

        case CASA_TESOURO:
            printf("Voce encontrou um tesouro!\n");

            /* Tesouro da XP ou um bonus de atributo */
            if (rand() % 2 == 0) {
                ganharXP(heroi, 25);
            } else {
                aplicarBonusAleatorio(heroi);
            }
            break;

        case CASA_CURA:
            printf("Voce encontrou medicamentos!\n");
            curarPersonagem(heroi, 30);
            printf("Voce recuperou ate 30 pontos de vida. Vida atual: %d/%d\n",
                   heroi->vida, heroi->vidaMaxima);
            break;

        case CASA_ARMADILHA:
            printf("VOCE CAIU EM UMA ARMADILHA!\n");
            receberDano(heroi, 15);
            printf("Voce perdeu 15 pontos de vida. Vida atual: %d/%d\n",
                   heroi->vida, heroi->vidaMaxima);

            if (!heroiVivo(heroi)) {
                printf("\nVoce morreu!\n");
                jogo->jogoFinalizado = 1;
                jogo->venceu = 0;
            }
            break;

        case CASA_MISSAO:
            printf("MISSAO DA FASE!\n");
            printf("Item encontrado: %s\n", fase->itemMissao);
            jogo->encontrouItemMissao = 1;

            printf("\nO chefe da fase apareceu!\n");
            jogo->monstroAtual = fase->monstros[TOTAL_MONSTROS - 1];
            jogo->emCombate = 1;
            jogo->combateChefe = 1;
            mostrarMonstro(&jogo->monstroAtual);
            break;
    }

    printf("==========================\n");
}
