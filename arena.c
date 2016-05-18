#include "arena.h"

Arena * arena_new(size_t data_size, uint32_t max_num) {
    int i;
    Arena * self;
    ArenaNode * ptr;
    size_t jump_size;
    char * next;

    jump_size = sizeof(ArenaNode) + data_size;

    self = (Arena *)malloc(sizeof(Arena) + jump_size * max_num);
    self->root = self->arr;
    self->data_size = data_size;

    ptr = self->arr;
    i = 0;
    while(1) {
        ptr->next = (ArenaNode *)(((char*)ptr) + jump_size);
        i ++;
        if (i >= max_num) {
            ptr = 0;
            break;
        }
        ptr = ptr->next;
    }

    return self;
}

void * arena_malloc(Arena * self) {
    ArenaNode * ptr;
    if (! self->root) {
        perror("ARENA OOM");
        exit(1);
    }
    ptr = self->root;
    self->root = ptr->next;
    return (void*)(ptr->data);
}

void * arena_calloc(Arena * self) {
    ArenaNode * ptr;
    if (! self->root) {
        perror("ARENA OOM");
        exit(1);
    }
    ptr = self->root;
    self->root = ptr->next;
    bzero(ptr->data, self->data_size);
    return (void*)(ptr->data);
}

void arena_dealloc(Arena * self, void * data) {
    ArenaNode * ptr;
    ptr = (ArenaNode *)(
        ((char *)data) - sizeof(struct ArenaNode *)
    );
    ptr->next = self->root;
    self->root = ptr;
}
