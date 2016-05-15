#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define StackOf(max_size, type) \
    struct { \
        int size; \
        int iter; \
        type arr[max_size]; \
    }

#define stack_init() {0}

#define stack_clear(stack) \
    ((stack)->size = 0)

#define stack_new(stack_type) \
    (calloc(1, sizeof(stack_type)))

#define stack_push(stack, val) \
    ((stack)->arr[(stack)->size++] = (val))

#define stack_pop(stack) \
    ((stack)->arr[--(stack)->size])

#define stack_get(stack, idx) \
    ((stack)->arr[idx])

#define stack_iter(var, stack) \
    for((stack)->iter = 0; \
        (var = (stack)->arr[(stack)->iter]), \
        (stack)->iter < (stack)->size; \
        (stack)->iter ++)

inline int _stack_has(void * stack, int s, uint64_t val) {
    int i;
    uint8_t * arr1;
    if(s == 1) {
        arr1 = (uint8_t *)(((int*)stack) + 2);
        for(i = 0; i < ((int*)stack)[0]; i++){
            if(arr1[i] == (uint8_t)val) return 1;
        }
        return 0;
    }
    else {
        perror("UNSUPPORTED STACK DATA SIZE\n");
        exit(1);
    }
    return 0;
}

#define stack_has(stack, val) \
    (_stack_has((void *)(stack), \
        sizeof((stack)->arr[0]), (uint64_t)val))

#define push stack_push
#define pop stack_pop

#endif
