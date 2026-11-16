#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrada.h"

/* Le uma linha inteira (descarta o excesso). Encerra o jogo em EOF. */
static void lerLinha(char *buffer, int tamanho) {

    if (fgets(buffer, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada. Saindo do jogo.\n");
        exit(0);
    }

    /* Se a linha era maior que o buffer, descarta o restante */
    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int lerOpcao(const char *mensagem, int min, int max) {

    char linha[64];
    char *fim;
    long valor;

    while (1) {

        printf("%s", mensagem);
        lerLinha(linha, sizeof(linha));

        valor = strtol(linha, &fim, 10);

        /* ignora espacos no final */
        while (*fim == ' ' || *fim == '\t' || *fim == '\r' || *fim == '\n') {
            fim++;
        }

        if (fim == linha || *fim != '\0') {
            printf("Entrada invalida! Digite apenas numeros.\n");
        } else if (valor < min || valor > max) {
            printf("Opcao invalida! Escolha entre %d e %d.\n", min, max);
        } else {
            return (int) valor;
        }
    }
}

void aguardarEnter(const char *mensagem) {

    char linha[64];

    printf("%s", mensagem);
    lerLinha(linha, sizeof(linha));
}
