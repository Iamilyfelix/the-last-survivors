#include <stdio.h>
#include <stdlib.h>

#include "estruturas.h"
#include "progressao.h"
#include "personagens.h"
#include "fases.h"

/* Soma XP ao personagem e verifica se ele subiu de nivel */
void ganharXP(Personagem *p, int xp) {

    p->experiencia += xp;

    printf("Voce ganhou %d de experiencia! (total: %d)\n", xp, p->experiencia);

    verificarNivel(p);
}

/* Sobe de nivel enquanto tiver XP suficiente (nivel x 100) */
void verificarNivel(Personagem *p) {

    while (p->experiencia >= p->nivel * 100) {

        p->nivel++;

        p->vidaMaxima += 10;
        curarPersonagem(p, 10);
        *atributoPrincipal(p) += 2;
        p->defesa += 1;

        printf("\n================================\n");
        printf("VOCE SUBIU DE NIVEL! Novo nivel: %d\n", p->nivel);
        printf("+10 vida maxima | +2 %s | +1 defesa | +10 vida atual\n",
               nomeAtributoPrincipal(p));
        printf("================================\n");
    }
}

/* Bonus aleatorio em um atributo (forca, defesa, agilidade, inteligencia ou vida maxima) */
void aplicarBonusAleatorio(Personagem *p) {

    printf("\n===== BONUS DE ATRIBUTO =====\n");

    switch (rand() % 5) {
        case 0:
            p->forca += 2;
            printf("Voce ganhou +2 de FORCA!\n");
            break;
        case 1:
            p->defesa += 2;
            printf("Voce ganhou +2 de DEFESA!\n");
            break;
        case 2:
            p->agilidade += 2;
            printf("Voce ganhou +2 de AGILIDADE!\n");
            break;
        case 3:
            p->inteligencia += 2;
            printf("Voce ganhou +2 de INTELIGENCIA!\n");
            break;
        default:
            p->vidaMaxima += 10;
            curarPersonagem(p, 10);
            printf("Voce ganhou +10 de VIDA MAXIMA!\n");
            break;
    }
}

/* Verifica se a missao da fase foi cumprida e avanca de fase ou vence o jogo */
void verificarAvancoFase(Jogo *jogo) {

    if (jogo->derrotouChefe == 1 && jogo->encontrouItemMissao == 1) {

        if (jogo->faseAtual == TOTAL_FASES - 1) {

            jogo->jogoFinalizado = 1;
            jogo->venceu = 1;

        } else {

            printf("\n================================\n");
            printf("MISSAO CONCLUIDA!\n");
            printf("Voce avancara para a proxima fase.\n");
            printf("================================\n");

            jogo->faseAtual++;
            jogo->posicao = 1;
            jogo->encontrouItemMissao = 0;
            jogo->derrotouChefe = 0;

            apresentarFase(&jogo->fases[jogo->faseAtual], jogo->faseAtual + 1);
        }
    }
}
