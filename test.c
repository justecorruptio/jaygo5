#define VERBOSE_TESTS 1

int __success, __failure;

#define assert(test) \
    printf("%c", (test)? \
        (__success++, '.') \
    : \
        (__failure++, 'F') \
    );

#if VERBOSE_TESTS
#define run_test(test) \
    printf(#test ": "); \
    test(); \
    printf("\n");
#else
#define run_test(test) \
    test();
#endif

#include "tests/test_board.c"

int main() {

    test_board();

#if VERBOSE_TESTS
    printf("Success: %d, Failure: %d",
        __success,
        __failure
    );
#endif
    printf("\n");
    return !!__failure;
}
