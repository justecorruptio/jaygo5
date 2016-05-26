#include "arena.h"
#include "board.h"
#include "playout.h"
#include "utils.h"

#define SPEED 0

int test() {
    Board * a;

    a = board_new();

    /*
    board_play(a, to_pos(0, 0), BLACK);
    board_play(a, to_pos(0, 2), BLACK);

    board_play(a, to_pos(1, 0), WHITE);
    board_play(a, to_pos(1, 2), WHITE);
    board_play(a, to_pos(0, 3), WHITE);
    board_play(a, to_pos(0, 1), WHITE);

    board_play(a, to_pos(1, 1), BLACK);
    board_play(a, to_pos(0, 0), BLACK); // SUICIDE
    board_play(a, to_pos(2, 0), BLACK);
    board_play(a, to_pos(0, 0), BLACK);
    board_play(a, to_pos(1, 0), WHITE); // KO
    board_play(a, to_pos(1, 0), BLACK);

    board_play(a, to_pos(2, 1), WHITE);
    board_play(a, to_pos(3, 0), WHITE);
    */

    board_play(a, to_pos(1, 0), WHITE);
    board_play(a, to_pos(0, 1), WHITE);
    board_play(a, to_pos(2, 1), WHITE);
    board_play(a, to_pos(1, 2), WHITE);

    board_play(a, to_pos(0, 2), BLACK);
    board_play(a, to_pos(2, 2), BLACK);

    printf("%d\n", _is_eye(a->goban, to_pos(1, 1), WHITE));

#if !SPEED
    board_print(a, stdout);
#endif
    board_free(a);
    return 0;
}

int main(int argc, char * argv[]){
    uint64_t i;
    double a, b;

    board_initialize();

    a = now();
#if SPEED
    for(i = 0 ; i < 10000000; i ++){
#else
    for(i = 0 ; i < 1; i ++){
#endif
        test();
    }
    b = now();

    printf("TIME: %f\n", b - a);

    board_destroy();

    return 0;
}
