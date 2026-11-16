#include <stdio.h>
#include <string.h>

#include "estruturas.h"
#include "personagens.h"
#include "entrada.h"

/* Cadastra os personagens do jogo */
void carregarPersonagens(Personagem personagens[]) {

    /* MARCUS - O SOLDADO (tanque, ataque principal: forca) */
    strcpy(personagens[0].nome, "Marcus");
    personagens[0].vida = 150;
    personagens[0].vidaMaxima = 150;
    personagens[0].forca = 15;
    personagens[0].defesa = 10;
    personagens[0].agilidade = 7;
    personagens[0].inteligencia = 6;
    personagens[0].experiencia = 0;
    personagens[0].nivel = 1;
    personagens[0].tipo = SOLDADO;
    personagens[0].habilidade = RAJADA_LETAL;
    strcpy(personagens[0].arma, "Fuzil de assalto");
    strcpy(personagens[0].armadura, "Colete militar");
    personagens[0].bonusArma = 4;
    personagens[0].bonusArmadura = 2;

    /* ELENA - A MEDICA (suporte, ataque principal: inteligencia) */
    strcpy(personagens[1].nome, "Elena");
    personagens[1].vida = 120;
    personagens[1].vidaMaxima = 120;
    personagens[1].forca = 7;
    personagens[1].defesa = 9;
    personagens[1].agilidade = 9;
    personagens[1].inteligencia = 15;
    personagens[1].experiencia = 0;
    personagens[1].nivel = 1;
    personagens[1].tipo = MEDICA;
    personagens[1].habilidade = PRIMEIROS_SOCORROS;
    strcpy(personagens[1].arma, "Pistola");
    strcpy(personagens[1].armadura, "Colete de protecao");
    personagens[1].bonusArma = 3;
    personagens[1].bonusArmadura = 2;

    /* ALEX - O SOBREVIVENTE (precisao, ataque principal: agilidade) */
    strcpy(personagens[2].nome, "Alex");
    personagens[2].vida = 135;
    personagens[2].vidaMaxima = 135;
    personagens[2].forca = 10;
    personagens[2].defesa = 9;
    personagens[2].agilidade = 15;
    personagens[2].inteligencia = 10;
    personagens[2].experiencia = 0;
    personagens[2].nivel = 1;
    personagens[2].tipo = SOBREVIVENTE;
    personagens[2].habilidade = ATAQUE_PRECISO;
    strcpy(personagens[2].arma, "Besta");
    strcpy(personagens[2].armadura, "Jaqueta reforcada");
    personagens[2].bonusArma = 5;
    personagens[2].bonusArmadura = 2;
}

/* Retorna o endereco do atributo principal da classe */
int *atributoPrincipal(Personagem *p) {

    switch (p->tipo) {
        case SOLDADO:  return &p->forca;
        case MEDICA:   return &p->inteligencia;
        default:       return &p->agilidade;
    }
}

const char *nomeAtributoPrincipal(const Personagem *p) {

    switch (p->tipo) {
        case SOLDADO:  return "Forca";
        case MEDICA:   return "Inteligencia";
        default:       return "Agilidade";
    }
}

/* Aplica dano ao personagem (nunca deixa a vida negativa) */
void receberDano(Personagem *p, int dano) {

    p->vida -= dano;

    if (p->vida < 0) {
        p->vida = 0;
    }
}

/* Cura o personagem (nunca passa da vida maxima) */
void curarPersonagem(Personagem *p, int quantidade) {

    p->vida += quantidade;

    if (p->vida > p->vidaMaxima) {
        p->vida = p->vidaMaxima;
    }
}

int heroiVivo(const Personagem *p) {
    return p->vida > 0;
}

/* Mostra a ficha do personagem */
void mostrarPersonagem(const Personagem *p) {

    printf("Vida: %d/%d | Forca: %d | Defesa: %d | Agilidade: %d | Inteligencia: %d\n",
           p->vida, p->vidaMaxima, p->forca, p->defesa,
           p->agilidade, p->inteligencia);
    printf("Arma: %s (+%d ataque) | Armadura: %s (+%d defesa)\n",
           p->arma, p->bonusArma, p->armadura, p->bonusArmadura);
}

/* Permite escolher um personagem */
void escolherPersonagem(Personagem personagens[], Personagem *jogador) {

    int opcao;

    printf("\n===== ESCOLHA SEU SOBREVIVENTE =====\n");

    for (int i = 0; i < TOTAL_PERSONAGENS; i++) {

        printf("\n[%d] %s (ataque principal: %s)\n", i + 1,
               personagens[i].nome, nomeAtributoPrincipal(&personagens[i]));
        mostrarPersonagem(&personagens[i]);

        switch (personagens[i].habilidade) {
            case RAJADA_LETAL:
                printf("Habilidade: Rajada Letal - dano alto que ignora a sorte do dado\n");
                break;
            case PRIMEIROS_SOCORROS:
                printf("Habilidade: Primeiros Socorros - cura vida (inteligencia x 3)\n");
                break;
            case ATAQUE_PRECISO:
                printf("Habilidade: Ataque Preciso - golpe que nunca erra, dano dobrado\n");
                break;
        }
    }

    opcao = lerOpcao("\nEscolha um personagem: ", 1, TOTAL_PERSONAGENS);

    /* Copia o personagem escolhido para o jogador */
    *jogador = personagens[opcao - 1];

    printf("\nVoce escolheu %s!\n", jogador->nome);
}
