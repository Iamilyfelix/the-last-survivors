#ifndef PROGRESSAO_H
#define PROGRESSAO_H

#include "estruturas.h"

void ganharXP(Personagem *p, int xp);
void verificarNivel(Personagem *p);
void aplicarBonusAleatorio(Personagem *p);
void verificarAvancoFase(Jogo *jogo);

#endif
