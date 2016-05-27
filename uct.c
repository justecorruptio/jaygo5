#include "uct.h"

Arena * UCT_NODE_ARENA;

int uct_initialize() {
    UCT_NODE_ARENA = arena_new(sizeof(UCTNode), 1000);
    return 1;
}

int uct_destroy() {
    arena_free(UCT_NODE_ARENA);
    return 1;
};
