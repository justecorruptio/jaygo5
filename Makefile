CC=gcc -O3 -g
SOURCES=utils.c board.c arena.c

all: jaygo

dev: dev.c $(SOURCES)
	$(CC) dev.c $(SOURCES) -o test_jaygo && test_jaygo
