#include "playout.h"

extern Pos TONARI[SIZE * SIZE][5];
extern Pos DIAGONALS[SIZE * SIZE][5];

int _is_eye(Color * goban, Pos pos, Color color) {
    Pos tonari, *t_ptr;
    Color other = color_other(color);
    int other_count = 0;

    if(goban[pos] != EMPTY) return 0;

    ITER(tonari, t_ptr, TONARI[pos])
        if(goban[tonari] != color) return 0;

    ITER(tonari, t_ptr, DIAGONALS[pos]) {
        if(goban[tonari] == other) other_count ++;
        if(other_count > 1) return 0;
    }

    if(other_count == 1 && t_ptr - DIAGONALS[pos] <= 2)
        return 0;

    return 1;
}

int _play_random_move(Board * board, Color color) {
    int i;
    Pos pos;
    Color * goban = board->goban;

    LOOP(i, 20) {
        pos = rand() % (SIZE * SIZE);
        if(goban[pos] != EMPTY) continue;
        if(_is_eye(goban, pos, color)) continue;
        if(board_play(board, pos, color)){
            return 1;
        }
    }
    return 0;
}

int _exhaust_random_move(Board * board, Color color) {
    Pos possible[SIZE * SIZE];
    Pos pos, * ptr;
    int count = 0, i;
    Color * goban = board->goban;

    LOOP(pos, SIZE * SIZE) {
        if(goban[pos] != EMPTY) continue;
        if(count == 0)
            possible[count] = pos;
        else {
            i = rand() % count;
            possible[count] = possible[i];
            possible[i] = pos;
        }
        count ++;
    }
    possible[count] = nil;
    ITER(pos, ptr, possible) {
        if(_is_eye(goban, pos, color)) continue;
        if(board_play(board, pos, color)) {
            return 1;
        }
    }
    return 0;
}

int playout_random_game(Board * board, Color color) {
    int i, passes = 0;
    LOOP(i, 200) {
        if(_play_random_move(board, color))
            passes = 0;
        else if(_exhaust_random_move(board, color))
            passes = 0;
        else
            passes ++;

        if(passes >= 2)
            return 1;
        color = color_other(color);
    }
    return 0;
}
