#include <stdio.h>
#include <string.h>

#include "estruturas.h"
#include "fases.h"
#include "monstros.h"

void carregarFases(Fase fases[]) {

    /* FASE 1 */
    strcpy(fases[0].nome, "Cidade Abandonada");
    strcpy(fases[0].historia,
           "As ruas estao tomadas por infectados. A saida da cidade esta trancada e so a chave do antigo guarda pode abri-la.");
    strcpy(fases[0].missao,
           "Encontrar a chave e derrotar o Guarda Infectado");
    strcpy(fases[0].itemMissao, "Chave da cidade");

    /* FASE 2 */
    strcpy(fases[1].nome, "Hospital Infectado");
    strcpy(fases[1].historia,
           "O hospital foi o primeiro foco do virus. Nos arquivos do medico estao as pesquisas que podem levar a cura.");
    strcpy(fases[1].missao,
           "Recuperar os documentos e derrotar o Medico Infectado");
    strcpy(fases[1].itemMissao, "Documentos de pesquisa");

    /* FASE 3 */
    strcpy(fases[2].nome, "Instalacao Militar");
    strcpy(fases[2].historia,
           "A base secreta guarda o laboratorio onde o virus nasceu. O general infectado protege a unica cura.");
    strcpy(fases[2].missao,
           "Derrotar o General Infectado e recuperar a cura");
    strcpy(fases[2].itemMissao, "Cura do virus");

    /* Cadastra os monstros de todas as fases */
    carregarMonstros(fases);
}

/* Mostra a historia e a missao da fase */
void apresentarFase(const Fase *fase, int numero) {

    printf("\n################################\n");
    printf("FASE %d: %s\n", numero, fase->nome);
    printf("################################\n");
    printf("%s\n", fase->historia);
    printf("MISSAO: %s\n", fase->missao);
}
