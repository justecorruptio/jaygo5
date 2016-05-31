#CC=gcc -O1 -g -lm -mmacosx-version-min=10.2
CC=gcc -O3 -g -lm
SOURCES=utils.c board.c arena.c playout.c uct.c
TEST_OPTS=-Wno-implicit-function-declaration

all: jaygo

dev: dev.c $(SOURCES)
	$(CC) dev.c $(SOURCES) -o test_jaygo && test_jaygo

test: test.c $(SOURCES)
	$(CC) test.c $(SOURCES) $(TEST_OPTS) -o test_jaygo && test_jaygo

jaygo: jaygo.c $(SOURCES)
	$(CC) jaygo.c $(SOURCES) -o jaygo
