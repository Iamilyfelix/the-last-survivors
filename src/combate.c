#include <stdio.h>
#include <stdlib.h>

#include "estruturas.h"
#include "combate.h"
#include "entrada.h"
#include "tabuleiro.h"
#include "personagens.h"
#include "monstros.h"
#include "progressao.h"

/* Dano = ataque - defesa, com minimo de 1 */
int calcularDano(int ataque, int defesa) {

    int dano = ataque - defesa;

    if (dano < 1) {
        dano = 1;
    }

    return dano;
}

/* Turno do monstro: rola d20, ataca e aplica o dano no heroi (por ponteiro) */
static void turnoMonstro(Jogo *jogo) {

    Personagem *heroi = &jogo->jogador;
    Monstro *monstro = &jogo->monstroAtual;

    int dado = rolarDado(20);

    printf("\n--- Turno do monstro ---\n");
    printf("%s tirou %d no d20.\n", monstro->nome, dado);

    if (dado <= 3) {
        printf("%s errou o ataque!\n", monstro->nome);
    } else {

        int ataque = monstro->ataque + dado / 2;
        int dano = calcularDano(ataque, heroi->defesa + heroi->bonusArmadura);

        if (jogo->defendendo == 1) {
            dano = dano / 2;
            if (dano < 1) {
                dano = 1;
            }
            printf("Sua defesa reduziu o dano!\n");
        }

        receberDano(heroi, dano);

        printf("%s causou %d de dano! Sua vida: %d/%d\n",
               monstro->nome, dano, heroi->vida, heroi->vidaMaxima);
    }

    jogo->defendendo = 0;
}

/* Ataque normal do jogador */
static void atacarMonstro(Jogo *jogo) {

    Personagem *heroi = &jogo->jogador;
    Monstro *monstro = &jogo->monstroAtual;

    int dado = rolarDado(20);
    int limiteCritico = (heroi->tipo == SOBREVIVENTE) ? 18 : 20;

    printf("\nVoce tirou %d no d20!\n", dado);

    if (dado <= 4) {
        printf("Voce errou o ataque!\n");
        return;
    }

    int ataque = *atributoPrincipal(heroi) + heroi->bonusArma + dado / 2;
    int dano = calcularDano(ataque, monstro->defesa);

    if (dado >= limiteCritico) {
        dano = dano * 2;
        printf("ACERTO CRITICO!\n");
    }

    danoNoMonstro(monstro, dano);

    printf("Voce causou %d de dano! Vida do inimigo: %d\n", dano, monstro->vida);
}

/* Habilidade especial (uma vez por combate) */
static void usarHabilidade(Jogo *jogo) {

    Personagem *heroi = &jogo->jogador;
    Monstro *monstro = &jogo->monstroAtual;
    int dano;

    switch (heroi->habilidade) {

        case RAJADA_LETAL:
            dano = calcularDano(*atributoPrincipal(heroi) + heroi->bonusArma + 15,
                                monstro->defesa);
            danoNoMonstro(monstro, dano);
            printf("\nRAJADA LETAL! Voce causou %d de dano! Vida do inimigo: %d\n",
                   dano, monstro->vida);
            break;

        case PRIMEIROS_SOCORROS:
            curarPersonagem(heroi, heroi->inteligencia * 3);
            printf("\nPRIMEIROS SOCORROS! Sua vida: %d/%d\n",
                   heroi->vida, heroi->vidaMaxima);
            break;

        case ATAQUE_PRECISO:
            dano = calcularDano(*atributoPrincipal(heroi) * 2 + heroi->bonusArma
                                + rolarDado(20) / 2,
                                monstro->defesa);
            danoNoMonstro(monstro, dano);
            printf("\nATAQUE PRECISO! Voce causou %d de dano! Vida do inimigo: %d\n",
                   dano, monstro->vida);
            break;
    }

    jogo->habilidadeUsada = 1;
}

/* Tenta fugir: d20 + agilidade/2 precisa ser pelo menos 11 */
static int fugirCombate(const Personagem *heroi) {

    int dado = rolarDado(20);

    printf("\nResultado da fuga: %d (+%d de agilidade)\n", dado, heroi->agilidade / 2);

    return (dado + heroi->agilidade / 2 >= 11);
}

/* Executa a acao escolhida. Retorna 0 se a acao nao gastou o turno. */
static int executarAcao(Jogo *jogo, AcaoCombate acao) {

    switch (acao) {

        case ACAO_ATACAR:
            atacarMonstro(jogo);
            break;

        case ACAO_DEFENDER:
            jogo->defendendo = 1;
            printf("\nVoce se preparou para defender!\n");
            break;

        case ACAO_HABILIDADE:
            if (jogo->habilidadeUsada == 1) {
                printf("\nVoce ja usou sua habilidade neste combate!\n");
                return 0;
            }
            usarHabilidade(jogo);
            break;

        case ACAO_FUGIR:
            if (fugirCombate(&jogo->jogador)) {
                printf("Voce conseguiu fugir!\n");
                jogo->fugiu = 1;
            } else {
                printf("Voce nao conseguiu fugir!\n");
            }
            break;
    }

    return 1;
}

/* Controla o combate completo por turnos */
void iniciarCombate(Jogo *jogo) {

    Personagem *heroi = &jogo->jogador;
    Monstro *monstro = &jogo->monstroAtual;

    jogo->defendendo = 0;
    jogo->habilidadeUsada = 0;
    jogo->fugiu = 0;

    printf("\n===== COMBATE INICIADO contra %s =====\n", monstro->nome);

    while (monstro->vida > 0 && heroi->vida > 0) {

        printf("\n===== SEU TURNO =====\n");
        printf("Sua vida: %d/%d | Vida do inimigo: %d\n",
               heroi->vida, heroi->vidaMaxima, monstro->vida);
        printf("[1] Atacar\n[2] Defender\n[3] Habilidade especial%s\n[4] Fugir\n",
               jogo->habilidadeUsada ? " (ja usada)" : "");

        AcaoCombate acao = (AcaoCombate) lerOpcao("\nEscolha: ", 1, 4);

        if (executarAcao(jogo, acao) == 0) {
            continue;   /* nao gastou o turno */
        }

        if (jogo->fugiu == 1 || monstro->vida <= 0) {
            break;
        }

        turnoMonstro(jogo);
    }

    if (!heroiVivo(heroi)) {

        printf("\nVoce foi derrotado!\n");
        jogo->jogoFinalizado = 1;
        jogo->venceu = 0;

    } else if (monstro->vida <= 0) {

        printf("\nVoce derrotou %s!\n", monstro->nome);

        /* Recompensa: XP + bonus aleatorio de atributo */
        ganharXP(heroi, monstro->experiencia);
        aplicarBonusAleatorio(heroi);

        if (jogo->combateChefe == 1) {
            jogo->derrotouChefe = 1;
        }
    }

    jogo->emCombate = 0;

    printf("\n===== FIM DO COMBATE =====\n");
}
