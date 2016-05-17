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

    //board_print(a, stdout);
    board_free(a);
    return 0;
}

int main(int argc, char * argv[]){

    uint64_t i;
    struct timeval a, b;

    board_initialize();

    gettimeofday(&a, 0);
    for(i = 0 ; i < 20000000; i ++){
        test();
    }
    gettimeofday(&b, 0);

    printf("TIME: %f\n", (b.tv_sec + .000001 * b.tv_usec -
        a.tv_sec - .000001 * a.tv_usec));

    return 0;
}
