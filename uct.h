#ifndef UCT_H
#define UCT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"
#include "board.h"

typedef struct UCTNode {
    uint32_t wins;
    uint32_t visits;
    Pos move;
    struct UCTNode * child;
    struct UCTNode * sibling;
} UCTNode;

int uct_initialize();
int uct_destroy();

#endif
