#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"
#include "utils.h"

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

#define to_pos(i, j) ((Pos)((i) * SIZE + (j)))

typedef struct Board {
    Pos possible_ko;
    uint8_t captures[2];
    Color goban[SIZE * SIZE];
} Board;

int board_initialize();
int board_destroy();
Board * board_new();
void board_free(Board * self);

Board * board_clone(Board * self);

int board_play(Board * self, Pos pos, Color color);
int board_print(Board * self, FILE * fh);

#endif
