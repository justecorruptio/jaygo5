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
