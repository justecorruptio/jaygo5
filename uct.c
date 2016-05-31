#include "uct.h"

Arena * UCT_NODE_ARENA;

int uct_initialize() {
    UCT_NODE_ARENA = arena_new(sizeof(UCTNode), 10000000);
    return 1;
}

int uct_destroy() {
    arena_free(UCT_NODE_ARENA);
    return 1;
}

UCTNode * uct_node_new(Pos pos) {
    UCTNode * self = (UCTNode *)arena_calloc(UCT_NODE_ARENA);
    self->move = pos;
    return self;
}

void uct_node_free(UCTNode * self) {
    if(self->child) uct_node_free(self->child);
    if(self->next) uct_node_free(self->next);
    arena_dealloc(UCT_NODE_ARENA, (void *) self);
}

void uct_node_free_except(UCTNode * self, UCTNode * subtree) {
    if(self->child && self->child != subtree)
        uct_node_free_except(self->child, subtree);
    if(self->next && self->next != subtree)
        uct_node_free_except(self->next, subtree);
    arena_dealloc(UCT_NODE_ARENA, (void *) self);
}

int create_children(UCTNode * self, Board * board, Color color) {
    Pos pos;
    Color * goban = board->goban;
    UCTNode * ptr, * t;

    ptr = 0;
    LOOP(pos, SIZE * SIZE) {
        if(goban[pos] == EMPTY && !is_eye(goban, pos, color)) {
            t = ptr;
            ptr = uct_node_new(pos);
            ptr->next = t;
        }
    }
    self->child = ptr;
    return 1;
}

UCTNode * uct_select(UCTNode * self, Board * board, Color color) {
    UCTNode * ptr, * best_ptr;
    float uct, best_uct = 0;

    while(1) {
        best_uct = 0;
        best_ptr = 0;
        for(ptr = self->child; ptr; ptr = ptr->next) {
            if(ptr->move == nil) continue;
            if(ptr->visits == 0)
                uct = 10000. + (rand() & 0xFF);
            else {
                uct = UCT_K * sqrtf(
                    logf(self->visits) / ptr->visits
                ) + 1.0 * ptr->wins / ptr->visits;
            }
            if(uct > best_uct) {
                best_uct = uct;
                best_ptr = ptr;
            }
        }
        if(board_play(board, best_ptr->move, color)) break;
        else best_ptr->move = nil;
    }
    return best_ptr;
}

int uct_play_random_game(Board * board, Color color) {
    Color winner;
    Board * clone = board_clone(board);
    playout_random_game(clone, color);
    winner = playout_find_winner(clone);
    board_free(clone);
    return winner == color;
}

int uct_simulate(UCTNode * self, Board * board, Color color) {
    int result;
    Pos move;
    UCTNode * ptr;

    if(!self->child && self->visits < UCT_MIN_VISITS)
        result = uct_play_random_game(board, color);
    else {
        if(!self->child) create_children(self, board, color);
        ptr = uct_select(self, board, color);
        result = 1 - uct_simulate(ptr, board, color_other(color));
    }
    self->visits ++;
    self->wins += 1 - result;

    return result;
}

Pos uct_best_move(UCTNode * self) {
    UCTNode * ptr, * best_ptr = 0;
    int most_visits = 0;
    Pos best_move = nil;

    for(ptr = self->child; ptr; ptr = ptr->next) {
        if(ptr->move == nil) continue;
        if(ptr->visits > most_visits) {
            most_visits = ptr->visits;
            best_ptr = ptr;
        }
    }
    best_move = best_ptr->move;
    printf("BEST_MOVE: [%d %d] %.2f%%\n",
        best_move / SIZE, best_move % SIZE,
        100.0 * best_ptr->wins / best_ptr->visits
    );
    return best_move;
}

Pos uct_search(Board * board, Color color) {
    int i;
    UCTNode * root, * ptr;
    Board * clone;
    Pos best_move;

    root = uct_node_new(nil);
    create_children(root, board, color);

    LOOP(i, UCT_SIMULATIONS) {
        clone = board_clone(board);
        uct_simulate(root, clone, color);
        //board_print(clone, stdout);
        board_free(clone);
    }
    best_move = uct_best_move(root);
    uct_node_free(root);
    return best_move;
}
