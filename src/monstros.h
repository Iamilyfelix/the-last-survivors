#ifndef MONSTROS_H
#define MONSTROS_H

#include "estruturas.h"

void carregarMonstros(Fase fases[]);
void danoNoMonstro(Monstro *m, int dano);
void mostrarMonstro(const Monstro *m);

#endif
