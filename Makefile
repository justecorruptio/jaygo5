CC=gcc -O3
SOURCES=utils.c board.c

all: jaygo

test: test.c $(SOURCES)
	$(CC) test.c $(SOURCES) -o test_jaygo && test_jaygo
