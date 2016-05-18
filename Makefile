CC=gcc -O3 -g
SOURCES=utils.c board.c arena.c

all: jaygo

test: test.c $(SOURCES)
	$(CC) test.c $(SOURCES) -o test_jaygo && test_jaygo
