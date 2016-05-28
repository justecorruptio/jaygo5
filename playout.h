#ifndef PLAYOUT_H
#define PLAYOUT_H

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "utils.h"

#define PLAY_RANDOM_MOVE_TRIES 15
#define PLAY_RANDOM_GAME_MAX_TURNS 200
#define PLAY_RANDOM_GAME_TRY_THRESHOLD 100

int _is_eye(Color * goban, Pos pos, Color color);
int playout_random_game(Board * board, Color color, int turn);

#endif
