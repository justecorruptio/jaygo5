#include "arena.h"
#include "board.h"
#include "playout.h"
#include "uct.h"
#include "utils.h"


int main(int argc, char * argv[]){
    Board * board;
    int x, y;

    board_initialize();
    uct_initialize();

    board = board_new();

    while(1) {
        board_print(board, stdout);
        printf("\nBlack: ");
        scanf("%d %d", &x, &y);
        board_play(board, to_pos(x, y), BLACK);
    }

    board_destroy();
    uct_destroy();
    return 0;
}
