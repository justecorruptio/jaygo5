#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct ArenaNode {
    struct ArenaNode * next;
    char data[];
} ArenaNode;

typedef struct Arena {
    struct ArenaNode * root;
    size_t data_size;
    struct ArenaNode arr[];
} Arena;


Arena * arena_new(size_t data_size, uint32_t max_num);
void * arena_malloc(Arena * self);
void * arena_calloc(Arena * self);
void arena_dealloc(Arena * self, void * data);

#define arena_free free

#endif
