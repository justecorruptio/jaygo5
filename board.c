#include "board.h"
#include "stack.h"
#include "utils.h"

typedef StackOf(4, Pos) TonariList;
TonariList TONARI[SIZE * SIZE];

int board_initialize() {
    int i, j;
    TonariList * tonari;
    loop(i, SIZE) {
        loop(j, SIZE) {
            tonari = &TONARI[to_pos(i, j)];
            if(i != 0) push(tonari, to_pos(i - 1, j));
            if(j != 0) push(tonari, to_pos(i, j - 1));
            if(i != SIZE - 1) push(tonari, to_pos(i + 1, j));
            if(j != SIZE - 1) push(tonari, to_pos(i, j + 1));
        }
    }
    return 1;
}

typedef StackOf(SIZE * SIZE, Pos) PosList;

int _has_lib(Color * goban, Pos pos) {
    Pos tonari;
    PosList frontier;
    PosList inspected;

    Color color;
    Color init_color = goban[pos];

    if(init_color == EMPTY) return 1;

    stack_clear(&frontier);
    stack_clear(&inspected);

    push(&inspected, pos);

    while(1) {
        stack_iter(tonari, &TONARI[pos]) {
            color = goban[tonari];
            if(color == EMPTY)
                return 1;
            else if(color == init_color &&
                ! stack_has(&inspected, tonari)
            )
                push(&frontier, tonari);
        }
        if(frontier.size == 0) return 0;
        pos = pop(&frontier);
        push(&inspected, pos);
    }
}

int _kill_group(Color * goban, Pos pos) {
    Pos tonari;
    PosList frontier;
    PosList inspected;

    int killed = 0;

    Color color;
    Color init_color = goban[pos];

    if (init_color == EMPTY) return 0;

    stack_clear(&frontier);
    stack_clear(&inspected);

    push(&inspected, pos);

    while(1) {
        goban[pos] = EMPTY;
        killed += 1;
        stack_iter(tonari, &TONARI[pos]) {
            color = goban[tonari];
            if(color == init_color &&
                ! stack_has(&inspected, tonari)
            )
                push(&frontier, tonari);
        }
        if(frontier.size == 0) return killed;
        pos = pop(&frontier);
        push(&inspected, pos);
    }
}

int board_play(Board * self, Pos pos, Color color) {
    Pos tonari;
    TonariList killing;

    if(self->goban[pos]) return 0;

    stack_clear(&killing);

    self->goban[pos] = color;

    stack_iter(tonari, &TONARI[pos]) {
        if(color == color_other(self->goban[tonari]) &&
            ! _has_lib(self->goban, tonari)
        )
            push(&killing, tonari);
    }
    if(killing.size == 0 && ! _has_lib(self->goban, pos)) {
        self->goban[pos] = EMPTY;
        return 0;
    }
    stack_iter(tonari, &killing) {
        self->captures[color - 1] +=
            _kill_group(self->goban, tonari);
    }

    return 1;
}

int board_print(Board * self, FILE * fh) {
    Color color;
    int i, j;
    loop(i, SIZE) {
        loop(j, SIZE) {
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
