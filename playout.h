#ifndef PLAYOUT_H
#define PLAYOUT_H

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "utils.h"

int _is_eye(Color * goban, Pos pos, Color color);
int playout_random_game(Board * board, Color color);

#endif
