#include <sys/time.h>

#include "board.h"
#include "set.h"
#include "stack.h"

typedef StackOf(4, Pos) Pos4;
extern Pos4 TONARI[SIZE*SIZE];

int test() {
    Board * a;

    a = board_new();

    board_play(a, to_pos(0, 0), BLACK);
    board_play(a, to_pos(0, 2), BLACK);

    board_play(a, to_pos(1, 0), WHITE);
    board_play(a, to_pos(1, 2), WHITE);
    board_play(a, to_pos(0, 3), WHITE);
    board_play(a, to_pos(0, 1), WHITE);

    board_play(a, to_pos(1, 1), BLACK);
    board_play(a, to_pos(2, 0), BLACK);
    board_play(a, to_pos(0, 0), BLACK);
    board_play(a, to_pos(1, 0), BLACK);

    board_play(a, to_pos(2, 1), WHITE);
    board_play(a, to_pos(3, 0), WHITE);

    //printf("LIB: %d\n", _has_lib(b->goban, to_pos(1, 1)));

    //board_print(a, stdout);
    board_free(a);
    return 0;
}

int main(int argc, char * argv[]){
    /*
    StackOf(32, Pos) t;

    Pos v;

    stack_clear(&t);
    stack_push(&t, 65);
    stack_push(&t, 10);
    //stack_iter(v, &t) { putchar(v); }
    printf("%d\n", stack_has(&t, 11));
    */

    /*
    SetOf(17, Pos) t;
    Pos v;
    set_clear(&t);
    printf("%lu\n", sizeof(*&t));
    set_add(&t, 15);
    set_add(&t, 14);
    printf("%d\n", set_has(&t, 14));
    */
    SetOf(81, Pos) t;
    printf("%lu\n", sizeof(*&t));

    uint64_t i;
    struct timeval a, b;

    board_initialize();

    gettimeofday(&a, 0);
    for(i = 0 ; i < 10000000; i ++){
        test();
    }
    gettimeofday(&b, 0);

    printf("TIME: %f\n", (b.tv_sec + .000001 * b.tv_usec -
        a.tv_sec - .000001 * a.tv_usec));

    return 0;
}
