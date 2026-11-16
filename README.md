# The Last Survivors

**Aluno:** Iamily Felix De Souza
** Matrícula : ** 20260013189
**Disciplina:** DCT1106 – Programação (BSI/UFRN) – 2026.2
**Padrão da linguagem:** C99 (compila com `gcc -std=c99`)

## História

Um vírus devastou o mundo e transformou milhões de pessoas em infectados. Poucos sobreviveram. Você controla um dos últimos sobreviventes e precisa atravessar três locais perigosos em busca da cura: a **Cidade Abandonada**, o **Hospital Infectado** e a **Instalação Militar**, onde o vírus nasceu. Em cada fase há um item de missão e um chefe que o protege. Só derrotando o chefe e pegando o item a fase é concluída. Ao vencer o General Infectado e recuperar a cura, a humanidade ganha uma nova chance.

## Personagens

O **ataque principal** de cada classe usa um atributo diferente (e é ele que sobe ao ganhar nível).

| Personagem | Classe | Vida | Força | Defesa | Agilidade | Inteligência | Ataque principal | Arma (bônus de ataque) | Armadura (bônus de defesa) |
|---|---|---|---|---|---|---|---|---|---|
| Marcus | Soldado | 150 | 15 | 10 | 7 | 6 | Força | Fuzil de assalto (+4) | Colete militar (+2) |
| Elena | Médica | 120 | 7 | 9 | 9 | 15 | Inteligência | Pistola (+3) | Colete de proteção (+2) |
| Alex | Sobrevivente | 135 | 10 | 9 | 15 | 10 | Agilidade | Besta (+5) | Jaqueta reforçada (+2) |

### Habilidades especiais (1 uso por combate)

| Personagem | Habilidade | Efeito |
|---|---|---|
| Marcus | Rajada Letal | Dano = atributo principal + bônus da arma + 15 − defesa do monstro (não depende do dado) |
| Elena | Primeiros Socorros | Recupera `inteligência × 3` pontos de vida |
| Alex | Ataque Preciso | Golpe que nunca erra: dano = `agilidade × 2` + bônus da arma + `d20/2` − defesa do monstro |

## Fases e monstros

O último monstro de cada fase é o **chefe**, que aparece na casa final (casa 12).

### Fase 1 – Cidade Abandonada
**Missão:** encontrar a chave e derrotar o Guarda Infectado.

| Monstro | Vida | Ataque | Defesa | Nível | XP |
|---|---|---|---|---|---|
| Zumbi comum | 30 | 6 | 2 | 1 | 20 |
| Corredor infectado | 25 | 9 | 1 | 1 | 20 |
| Guarda infectado (chefe) | 60 | 12 | 5 | 1 | 60 |

### Fase 2 – Hospital Infectado
**Missão:** recuperar os documentos de pesquisa e derrotar o Médico Infectado.

| Monstro | Vida | Ataque | Defesa | Nível | XP |
|---|---|---|---|---|---|
| Enfermeiro infectado | 65 | 10 | 5 | 2 | 35 |
| Zumbi mutante | 85 | 13 | 7 | 2 | 35 |
| Médico infectado (chefe) | 110 | 15 | 9 | 2 | 60 |

### Fase 3 – Instalação Militar
**Missão:** derrotar o General Infectado e recuperar a cura.

| Monstro | Vida | Ataque | Defesa | Nível | XP |
|---|---|---|---|---|---|
| Soldado infectado | 100 | 15 | 8 | 3 | 35 |
| Experimento mutante | 130 | 19 | 10 | 3 | 35 |
| General infectado (chefe) | 180 | 22 | 12 | 3 | 60 |

A dificuldade cresce a cada fase pelos atributos e pelo nível dos monstros.

## Dinâmica do jogo

### Tabuleiro e movimentação
- Cada fase tem um tabuleiro de **12 casas** (vetor de `TipoCasa`). O jogador começa na casa 1.
- A cada rodada o jogador aperta ENTER e rola um **d6**, avançando essa quantidade de casas. O jogador nunca passa da casa 12 nem fica antes da casa 1.
- O evento da casa onde ele parou é executado.

### Tipos de casa

| Casa | Evento |
|---|---|
| Vazia | Nada acontece |
| Combate | Aparece um dos dois monstros comuns da fase |
| Tesouro | Sorteio entre +25 de XP ou um bônus aleatório de atributo |
| Cura | Recupera 30 de vida (até a vida máxima) |
| Armadilha | Perde 15 de vida |
| Missão / Chefe | Encontra o item da missão e enfrenta o chefe da fase |

### Combate por turnos
A cada turno o jogador escolhe: **[1] Atacar, [2] Defender, [3] Habilidade especial ou [4] Fugir**. Depois o monstro age. O combate termina quando um dos lados chega a 0 de vida ou quando o jogador foge.

| Cálculo | Fórmula |
|---|---|
| Ataque do jogador | `d20/2 + atributo principal + bônus da arma` (erra se o d20 for ≤ 4) |
| Acerto crítico | d20 = 20 (Alex: d20 ≥ 18) dobra o dano |
| Dano ao monstro | `max(1, ataque − defesa do monstro)` |
| Ataque do monstro | `ataque base + d20/2` (erra se o d20 for ≤ 3) |
| Dano ao jogador | `max(1, ataque − (defesa + bônus da armadura))` |
| Defender | Reduz pela metade o dano do próximo ataque do monstro |
| Fugir | Funciona se `d20 + agilidade/2 ≥ 11`. Fugir do chefe faz o jogador recuar para a casa 8 |

### Recompensas e evolução
- Ao derrotar um monstro o jogador ganha **XP** e um **bônus aleatório** de +2 em força, defesa, agilidade ou inteligência, ou +10 de vida máxima.
- **Nível:** o jogador sobe de nível quando o XP total atinge `nível × 100`. A cada nível: +10 de vida máxima, +10 de vida atual, +2 no atributo principal e +1 de defesa.

### Vitória e derrota
- A fase só termina quando o jogador **pegou o item da missão e derrotou o chefe**. Então a próxima fase é liberada.
- **Vitória:** concluir a missão da fase 3 (derrotar o General e pegar a cura).
- **Derrota:** a vida do herói chega a 0 (em combate ou em armadilha).

## Como compilar e jogar

**Pré-requisito:** `gcc` (Linux: `sudo apt install build-essential`; macOS: `xcode-select --install`; Windows: MinGW-w64 ou WSL).

**Linux / macOS / WSL**
```bash
make
./jogo
```
ou, sem o `make`:
```bash
gcc -Wall -Wextra -std=c99 -o jogo src/*.c -lm
./jogo
```

**Windows (MinGW, PowerShell/CMD)**
```bat
gcc -Wall -Wextra -std=c99 -o jogo.exe src/main.c src/combate.c src/entrada.c src/eventos.c src/fases.c src/monstros.c src/personagens.c src/progressao.c src/tabuleiro.c -lm
jogo.exe
```

## Estrutura do código

```
.
├── README.md
├── Makefile
├── src/
│   ├── main.c          # loop principal do jogo
│   ├── estruturas.h    # structs e enums
│   ├── personagens.c/h # criação/escolha do herói, dano e cura por ponteiro
│   ├── monstros.c/h    # monstros das fases e dano no monstro por ponteiro
│   ├── fases.c/h       # fases, história e missões
│   ├── tabuleiro.c/h   # tabuleiro, dado e movimentação
│   ├── eventos.c/h     # eventos de cada tipo de casa
│   ├── combate.c/h     # combate por turnos
│   ├── progressao.c/h  # XP, nível, bônus aleatório e avanço de fase
│   └── entrada.c/h     # leitura segura de entradas
└── video/              # link do vídeo
```

### Principais estruturas
- **Enums:** `TipoPersonagem`, `TipoHabilidade`, `TipoCasa` e `AcaoCombate`.
- **Structs:** `Personagem`, `Monstro`, `Fase` (história, missão, monstros e casas) e `Jogo` (estado geral da partida).

### Uso de ponteiros
Os status são atualizados sempre por funções que recebem o endereço da struct, sem devolver cópias:
- `receberDano(Personagem *p, int dano)`, `curarPersonagem(Personagem *p, int quantidade)`
- `danoNoMonstro(Monstro *m, int dano)`
- `ganharXP(Personagem *p, int xp)`, `verificarNivel(Personagem *p)`, `aplicarBonusAleatorio(Personagem *p)`
- `moverJogador(int *posicao)`, `executarEvento(Jogo *jogo)`, `iniciarCombate(Jogo *jogo)`
- `atributoPrincipal(Personagem *p)` devolve o endereço do atributo principal da classe.

### Robustez
Toda entrada é lida por `lerOpcao()` (usa `fgets` + `strtol`): letras, números fora do menu e linhas em branco são recusados e o jogo não trava, nem mesmo com fim de entrada (EOF).

## Vídeo de demonstração
[Assista aqui](https://youtu.be/GrCKfZEdieQ)
