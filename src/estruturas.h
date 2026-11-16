#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define TOTAL_PERSONAGENS 3
#define TOTAL_MONSTROS 3
#define TOTAL_FASES 3
#define TOTAL_CASAS 12

/* Classes dos personagens jogaveis */
typedef enum {
    SOLDADO,
    MEDICA,
    SOBREVIVENTE
} TipoPersonagem;

/* Habilidade especial de cada personagem */
typedef enum {
    RAJADA_LETAL,
    PRIMEIROS_SOCORROS,
    ATAQUE_PRECISO
} TipoHabilidade;

/* Tipos de casa do tabuleiro */
typedef enum {
    CASA_VAZIA,
    CASA_COMBATE,
    CASA_TESOURO,
    CASA_CURA,
    CASA_ARMADILHA,
    CASA_MISSAO
} TipoCasa;

/* Acoes disponiveis durante o combate (valores = opcoes do menu) */
typedef enum {
    ACAO_ATACAR = 1,
    ACAO_DEFENDER,
    ACAO_HABILIDADE,
    ACAO_FUGIR
} AcaoCombate;

/* Personagem jogavel */
typedef struct {
    char nome[30];

    int vida;
    int vidaMaxima;
    int forca;
    int defesa;
    int agilidade;
    int inteligencia;

    int experiencia;
    int nivel;

    TipoPersonagem tipo;
    TipoHabilidade habilidade;

    char arma[30];
    char armadura[30];
    int bonusArma;      /* somado ao ataque */
    int bonusArmadura;  /* somado a defesa  */
} Personagem;

/* Monstro (inimigo) */
typedef struct {
    char nome[30];
    char descricao[100];

    int vida;
    int ataque;
    int defesa;
    int nivel;
    int experiencia;
} Monstro;

/* Fase do jogo: historia, missao, monstros e tabuleiro */
typedef struct {
    char nome[40];
    char historia[200];
    char missao[100];
    char itemMissao[40];

    Monstro monstros[TOTAL_MONSTROS];  /* o ultimo e o chefe */
    TipoCasa casas[TOTAL_CASAS];

    int quantidadeMonstros;
} Fase;

/* Estado geral do jogo */
typedef struct {
    Personagem jogador;
    Fase fases[TOTAL_FASES];

    int faseAtual;
    int posicao;

    int encontrouItemMissao;
    int derrotouChefe;

    int jogoFinalizado;
    int venceu;

    Monstro monstroAtual;
    int emCombate;
    int combateChefe;   /* 1 se o combate atual e contra o chefe */
    int fugiu;          /* 1 se o jogador fugiu do ultimo combate */

    int defendendo;
    int habilidadeUsada;
} Jogo;

#endif
