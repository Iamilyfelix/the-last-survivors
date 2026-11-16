#include <stdio.h>
#include <string.h>

#include "estruturas.h"
#include "monstros.h"

/* Cadastra os monstros de todas as fases (o ultimo de cada fase e o chefe) */
void carregarMonstros(Fase fases[]) {

    /* ===== FASE 1 - CIDADE ABANDONADA (nivel 1) ===== */

    strcpy(fases[0].monstros[0].nome, "Zumbi comum");
    strcpy(fases[0].monstros[0].descricao, "Um morto-vivo lento que vaga pelas ruas.");
    fases[0].monstros[0].vida = 30;
    fases[0].monstros[0].ataque = 6;
    fases[0].monstros[0].defesa = 2;
    fases[0].monstros[0].nivel = 1;
    fases[0].monstros[0].experiencia = 20;

    strcpy(fases[0].monstros[1].nome, "Corredor infectado");
    strcpy(fases[0].monstros[1].descricao, "Infectado muito rapido, ataca sem parar.");
    fases[0].monstros[1].vida = 25;
    fases[0].monstros[1].ataque = 9;
    fases[0].monstros[1].defesa = 1;
    fases[0].monstros[1].nivel = 1;
    fases[0].monstros[1].experiencia = 20;

    strcpy(fases[0].monstros[2].nome, "Guarda infectado");
    strcpy(fases[0].monstros[2].descricao, "Ex-guarda da cidade, protege a chave. (CHEFE)");
    fases[0].monstros[2].vida = 60;
    fases[0].monstros[2].ataque = 12;
    fases[0].monstros[2].defesa = 5;
    fases[0].monstros[2].nivel = 1;
    fases[0].monstros[2].experiencia = 60;

    /* ===== FASE 2 - HOSPITAL INFECTADO (nivel 2) ===== */

    strcpy(fases[1].monstros[0].nome, "Enfermeiro infectado");
    strcpy(fases[1].monstros[0].descricao, "Vaga pelos corredores com seringas na mao.");
    fases[1].monstros[0].vida = 65;
    fases[1].monstros[0].ataque = 10;
    fases[1].monstros[0].defesa = 5;
    fases[1].monstros[0].nivel = 2;
    fases[1].monstros[0].experiencia = 35;

    strcpy(fases[1].monstros[1].nome, "Zumbi mutante");
    strcpy(fases[1].monstros[1].descricao, "Paciente que sofreu mutacao, forte e agressivo.");
    fases[1].monstros[1].vida = 85;
    fases[1].monstros[1].ataque = 13;
    fases[1].monstros[1].defesa = 7;
    fases[1].monstros[1].nivel = 2;
    fases[1].monstros[1].experiencia = 35;

    strcpy(fases[1].monstros[2].nome, "Medico infectado");
    strcpy(fases[1].monstros[2].descricao, "Guarda os documentos de pesquisa. (CHEFE)");
    fases[1].monstros[2].vida = 110;
    fases[1].monstros[2].ataque = 15;
    fases[1].monstros[2].defesa = 9;
    fases[1].monstros[2].nivel = 2;
    fases[1].monstros[2].experiencia = 60;

    /* ===== FASE 3 - INSTALACAO MILITAR (nivel 3) ===== */

    strcpy(fases[2].monstros[0].nome, "Soldado infectado");
    strcpy(fases[2].monstros[0].descricao, "Soldado treinado que ainda empunha armas.");
    fases[2].monstros[0].vida = 100;
    fases[2].monstros[0].ataque = 15;
    fases[2].monstros[0].defesa = 8;
    fases[2].monstros[0].nivel = 3;
    fases[2].monstros[0].experiencia = 35;

    strcpy(fases[2].monstros[1].nome, "Experimento mutante");
    strcpy(fases[2].monstros[1].descricao, "Criatura de laboratorio, fruto de testes secretos.");
    fases[2].monstros[1].vida = 130;
    fases[2].monstros[1].ataque = 19;
    fases[2].monstros[1].defesa = 10;
    fases[2].monstros[1].nivel = 3;
    fases[2].monstros[1].experiencia = 35;

    strcpy(fases[2].monstros[2].nome, "General infectado");
    strcpy(fases[2].monstros[2].descricao, "Comandante da base, guarda a cura. (CHEFE)");
    fases[2].monstros[2].vida = 180;
    fases[2].monstros[2].ataque = 22;
    fases[2].monstros[2].defesa = 12;
    fases[2].monstros[2].nivel = 3;
    fases[2].monstros[2].experiencia = 60;

    /* Cada fase possui tres monstros */
    for (int i = 0; i < TOTAL_FASES; i++) {
        fases[i].quantidadeMonstros = TOTAL_MONSTROS;
    }
}

/* Aplica dano ao monstro (nunca deixa a vida negativa) */
void danoNoMonstro(Monstro *m, int dano) {

    m->vida -= dano;

    if (m->vida < 0) {
        m->vida = 0;
    }
}

void mostrarMonstro(const Monstro *m) {

    printf("Inimigo: %s (nivel %d)\n", m->nome, m->nivel);
    printf("Descricao: %s\n", m->descricao);
    printf("Vida: %d | Ataque: %d | Defesa: %d\n", m->vida, m->ataque, m->defesa);
}
