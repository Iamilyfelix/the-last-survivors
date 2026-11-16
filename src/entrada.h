#ifndef ENTRADA_H
#define ENTRADA_H

/* Le um inteiro entre min e max, repetindo ate a entrada ser valida.
   Se a entrada terminar (EOF), encerra o programa sem travar. */
int lerOpcao(const char *mensagem, int min, int max);

/* Espera o jogador apertar ENTER */
void aguardarEnter(const char *mensagem);

#endif
