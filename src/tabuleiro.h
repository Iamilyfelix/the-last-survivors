#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "estruturas.h"

void prepararTabuleiro(Fase fases[]);
int rolarDado(int lados);
void moverJogador(int *posicao);
void exibirTabuleiro(const Fase *fase, int posicao);

#endif
