#ifndef PERSONAGENS_H
#define PERSONAGENS_H

#include "estruturas.h"

void carregarPersonagens(Personagem personagens[]);
void escolherPersonagem(Personagem personagens[], Personagem *jogador);

/* Funcoes que alteram o personagem por ponteiro */
void receberDano(Personagem *p, int dano);
void curarPersonagem(Personagem *p, int quantidade);
int heroiVivo(const Personagem *p);

/* Atributo principal da classe (usado no ataque) */
int *atributoPrincipal(Personagem *p);
const char *nomeAtributoPrincipal(const Personagem *p);

void mostrarPersonagem(const Personagem *p);

#endif
