#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#define SIZE 9
#define KOMI 6.5

#define IS_HOSHI(i, j) \
    ((i == 2 || i == 6) && (j == 2 || j == 6))

typedef uint8_t Color;

#define color_other(c) \
    (3 - (c))

typedef int8_t Pos;

#define POS_END (-1)
#define to_pos(i, j) ((Pos)((i) * SIZE + (j)))
#define iter_pos(var, array) \
    for(var = (array); *(var) != POS_END; (var) ++)

typedef struct Board {
    struct Board * last;
    uint8_t captures[2];
    Color goban[SIZE * SIZE];
} Board;

/*
#define board_new() \
    ((Board *)calloc(1, sizeof(Board)))

#define board_clone(self) \
    ((Board *)memcpy( \
        malloc(sizeof(Board)), (self), sizeof(Board)))

#define board_free free
*/

int board_initialize();
int board_destroy();
Board * board_new();
void board_free(Board * self);

int board_play(Board * self, Pos pos, Color color);
int board_print(Board * self, FILE * fh);

int _has_lib(Color * goban, Pos pos);

#endif
