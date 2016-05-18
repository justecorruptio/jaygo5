#include "arena.h"
#include "board.h"
#include "utils.h"

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

    /*
    board_play(a, to_pos(0, 0), BLACK);
    board_play(a, to_pos(1, 1), BLACK);
    board_play(a, to_pos(1, 0), WHITE);
    board_play(a, to_pos(2, 1), WHITE);
    board_play(a, to_pos(3, 0), WHITE);

    board_play(a, to_pos(2, 0), BLACK);
    board_play(a, to_pos(1, 0), WHITE);
    */

    //board_print(a, stdout);
    board_free(a);
    return 0;
}

int main(int argc, char * argv[]){
    /*
    Board * a;

    Arena * arena = arena_new(sizeof(Board), 1024);

    printf("%p\n", arena->root);
    a = arena_calloc(arena);
    printf("%p\n", arena->root);
    printf("%p\n", a);
    printf("%lx\n", sizeof(Board));

    arena_dealloc(arena, a);
    printf("%p\n", arena->root);

    arena_free(arena);
    */

    uint64_t i;
    double a, b;

    board_initialize();

    a = now();
    for(i = 0 ; i < 10000000; i ++){
        test();
    }
    b = now();

    printf("TIME: %f\n", b - a);

    board_destroy();

    return 0;
}
