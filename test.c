#include "board.h"
#include "stack.h"

typedef StackOf(4, Pos) Pos4;
extern Pos4 TONARI[SIZE*SIZE];

int main(int argc, char * argv[]){
    /*
    StackOf(32, Pos) t = stack_init();

    Pos v;

    stack_push(&t, 65);
    stack_push(&t, 10);
    //stack_iter(v, &t) { putchar(v); }
    printf("%d\n", stack_has(&t, 11));
    */


    Board * a, * b;

    board_initialize();
    printf("%d\n", stack_get(&TONARI[0], 0));

    a = board_new();

    board_play(a, to_pos(0, 0), BLACK);
    board_play(a, to_pos(0, 2), BLACK);

    board_play(a, to_pos(1, 0), WHITE);
    board_play(a, to_pos(1, 2), WHITE);
    board_play(a, to_pos(0, 3), WHITE);

    board_play(a, to_pos(0, 1), WHITE);

    b = board_clone(a);

    printf("LIB: %d\n", _has_lib(b->goban, to_pos(1, 1)));

    board_print(b, stdout);
    board_free(a);
    board_free(b);
}
