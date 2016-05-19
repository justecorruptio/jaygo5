#include "arena.h"
#include "board.h"
#include "utils.h"

Pos TONARI[SIZE * SIZE][5];
Arena * ARENA;

int board_initialize() {
    int i, j;
    Pos * tonari;
    LOOP(i, SIZE) {
        LOOP(j, SIZE) {
            tonari = TONARI[to_pos(i, j)];
            if(i != 0) *(tonari++) = to_pos(i - 1, j);
            if(j != 0) *(tonari++) = to_pos(i, j - 1);
            if(i != SIZE - 1) *(tonari++) = to_pos(i + 1, j);
            if(j != SIZE - 1) *(tonari++) = to_pos(i, j + 1);
            *tonari = nil;
        }
    }

    ARENA = arena_new(sizeof(Board), 1024);
    return 1;
}

int board_destroy() {
    arena_free(ARENA);
    return 1;
}

Board * board_new() {
    Board * self = (Board *)arena_calloc(ARENA);
    self->possible_ko = nil;
    return self;
}

void board_free(Board * self) {
    arena_dealloc(ARENA, (void *)self);
}

Board * board_clone(Board * self) {
    return (Board *)memcpy(
        arena_calloc(ARENA),
        self,
        sizeof(Board)
    );
}

int _search(Pos val, Pos * start, Pos * end) {
    Pos * ptr;
    for(ptr = start; ptr < end; ptr ++)
        if (*ptr == val) return 1;
    return 0;
}

int _has_lib(Color * goban, Pos pos) {
    Pos tonari, *t;
    Pos arr[SIZE * SIZE];
    Pos * frontier = arr, * end = arr;

    Color color, orig = goban[pos];

    *(end++) = pos;
    frontier = end;

    while(1) {
        ITER(tonari, t, TONARI[pos]) {
            color = goban[tonari];
            if(color == EMPTY) return 1;
            if(color == orig && !_search(tonari, arr, frontier))
                *(end++) = tonari;
        }
        if(frontier == end) return 0;
        pos = *(frontier++);
    }
}

int _kill_group(Color * goban, Pos pos) {
    Pos tonari, *t;
    Pos arr[SIZE * SIZE];
    Pos * frontier = arr, * end = arr;

    int killed = 0;

    Color color, orig = goban[pos];

    if (orig == EMPTY) return 0;

    *(end++) = pos;
    frontier = end;

    while(1) {
        goban[pos] = EMPTY;
        killed += 1;
        ITER(tonari, t, TONARI[pos]) {
            color = goban[tonari];
            if(color == orig && !_search(tonari, arr, frontier))
                *(end++) = tonari;
        }
        if(frontier == end) return killed;
        pos = *(frontier++);
    }
}

int board_play(Board * self, Pos pos, Color color) {
    int captures = 0;
    Pos tonari, *t;
    Pos killing[5], *k_ptr = killing;
    Color * goban = self->goban;
    Color opponent = color_other(color);

    if(goban[pos] != EMPTY) return 0;

    goban[pos] = color;

    ITER(tonari, t, TONARI[pos]) {
        if(goban[tonari] == opponent && !_has_lib(goban, tonari))
            *(k_ptr++) = tonari;
    }
    *k_ptr = nil;

    if(k_ptr == killing) { // Empty killing list
        if(_has_lib(goban, pos)) {
            self->possible_ko = nil;
            return 1;
        }
        else {
            goban[pos] = EMPTY;
            return 0;
        }
    }

    ITER(tonari, t, killing)
        captures += _kill_group(goban, tonari);

    if (captures == 1 && self->possible_ko == killing[0]) {
        goban[pos] = EMPTY;
        goban[killing[0]] = opponent;
        return 0;
    }

    self->possible_ko = (captures == 1 ? pos : nil);
    self->captures[color - 1] += captures;

    return 1;
}

int board_print(Board * self, FILE * fh) {
    Color color;
    int i, j;
    LOOP(i, SIZE) {
        LOOP(j, SIZE) {
            color = self->goban[to_pos(i, j)];
            fprintf(fh, "%c ", color == EMPTY ?
                IS_HOSHI(i, j) ? '+' : '.'
            :
                color == BLACK ? 'X' : 'O'
            );
        }
        fprintf(fh, "\n");
    }
    fprintf(fh, "X:%d, O:%d+%.1f\n",
        self->captures[0],
        self->captures[1],
        KOMI
    );
    return 0;
}
