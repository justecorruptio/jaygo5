#ifndef UCT_H
#define UCT_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"
#include "board.h"
#include "playout.h"
#include "utils.h"

#define UCT_SIMULATIONS 2000000
#define UCT_MIN_VISITS 10
#define UCT_K .7

typedef struct UCTNode {
    uint32_t wins;
    uint32_t visits;
    Pos move;
    struct UCTNode * child;
    struct UCTNode * next;
} UCTNode;

Pos uct_search(Board * board, Color color);

int uct_initialize();
int uct_destroy();

#endif
