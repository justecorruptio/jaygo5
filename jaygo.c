#include "arena.h"
#include "board.h"
#include "playout.h"
#include "uct.h"
#include "utils.h"


int main(int argc, char * argv[]){
    Board * board;
    int x, y;
    Pos pos;
    UCTNode * uct_tree = 0;
    UCTNode * ptr;

    board_initialize();
    uct_initialize();

    board = board_new();

    while(1) {
        board_print(board, stdout);
        printf("\nBlack: ");
        if(scanf("%d %d", &x, &y) == -1)
            break;
        board_play(board, to_pos(x, y), BLACK);

        board_print(board, stdout);
        pos = uct_search(board, WHITE);
        board_play(board, pos, WHITE);
    }

    //for(ptr = uct_tree->child; ptr; ptr = ptr->next)
    //    printf("%d ", ptr->move);

    puts("");

    board_destroy();
    uct_destroy();
    return 0;
}
