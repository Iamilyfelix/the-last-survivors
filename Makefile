CC     = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC    = $(wildcard src/*.c)

jogo: $(SRC) $(wildcard src/*.h)
	$(CC) $(CFLAGS) -o jogo $(SRC) -lm

clean:
	rm -f jogo
