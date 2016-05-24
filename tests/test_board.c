#include "../board.h"


void test_to_pos() {
    assert(to_pos(0, 0) == 0);
    assert(to_pos(0, 3) == 3);
    assert(to_pos(3, 0) == SIZE * 3);
    assert(to_pos(3, 3) == SIZE * 3 + 3);
}

void test_search() {
    Pos pos[4] = {1, 2, 3, 4};

    assert(_search(1, pos, pos + 4));
    assert(!_search(5, pos, pos + 4));
}

void test_has_libs_001() {
    Board * board = board_new();
    board->goban[to_pos(0, 1)] = BLACK;
    board->goban[to_pos(1, 0)] = BLACK;
    board->goban[to_pos(1, 0)] = WHITE;

    assert(!_has_lib(board->goban, to_pos(0, 0)));
    assert(_has_lib(board->goban, to_pos(1, 0)));

    board_free(board);
}

void test_has_libs_002() {
    Board * board = board_new();
    board->goban[to_pos(0, 0)] = BLACK;
    board->goban[to_pos(1, 0)] = BLACK;
    board->goban[to_pos(0, 1)] = WHITE;

    assert(_has_lib(board->goban, to_pos(0, 0)));
    assert(_has_lib(board->goban, to_pos(1, 0)));

    board_free(board);
}

void test_has_libs_003() {
    Board * board = board_new();
    board->goban[to_pos(0, 0)] = BLACK;
    board->goban[to_pos(1, 0)] = BLACK;
    board->goban[to_pos(0, 1)] = WHITE;
    board->goban[to_pos(1, 1)] = WHITE;
    board->goban[to_pos(2, 0)] = WHITE;

    assert(!_has_lib(board->goban, to_pos(0, 0)));
    assert(!_has_lib(board->goban, to_pos(1, 0)));

    board_free(board);
}

void test_kill_group_001() {
    Board * board = board_new();
    board->goban[to_pos(0, 0)] = BLACK;

    assert(_kill_group(board->goban, to_pos(0, 0)) == 1);
    assert(board->goban[to_pos(0, 0)] == EMPTY);

    board_free(board);
}

void test_kill_group_002() {
    Board * board = board_new();
    board->goban[to_pos(0, 0)] = BLACK;
    board->goban[to_pos(0, 1)] = BLACK;
    board->goban[to_pos(1, 1)] = BLACK;

    assert(_kill_group(board->goban, to_pos(0, 1)) == 3);
    assert(board->goban[to_pos(0, 0)] == EMPTY);
    assert(board->goban[to_pos(0, 1)] == EMPTY);
    assert(board->goban[to_pos(1, 1)] == EMPTY);

    board_free(board);
}

void test_board_play_001() {
    Board * board = board_new();

    assert(board_play(board, to_pos(0, 0), BLACK));
    assert(board->goban[to_pos(0, 0)] == BLACK);

    board_free(board);
}

void test_board_play_002_illegal() {
    Board * board = board_new();
    board->goban[to_pos(0, 0)] = BLACK;

    assert(!board_play(board, to_pos(0, 0), BLACK));

    board_free(board);
}

void test_board_play_003_capture() {
    Board * board = board_new();
    board->goban[to_pos(0, 0)] = BLACK;
    board->goban[to_pos(2, 0)] = BLACK;
    board->goban[to_pos(0, 1)] = WHITE;
    board->goban[to_pos(2, 1)] = WHITE;
    board->goban[to_pos(3, 0)] = WHITE;

    assert(board_play(board, to_pos(1, 0), WHITE));
    assert(board->goban[to_pos(0, 0)] == EMPTY);
    assert(board->goban[to_pos(2, 0)] == EMPTY);
    assert(board->captures[1] == 2);

    board_free(board);
}

void test_board_play_004_ko() {
    Board * board = board_new();
    board->goban[to_pos(0, 0)] = BLACK;
    board->goban[to_pos(1, 1)] = BLACK;
    board->goban[to_pos(1, 0)] = WHITE;
    board->goban[to_pos(2, 1)] = WHITE;
    board->goban[to_pos(3, 0)] = WHITE;

    assert(board_play(board, to_pos(2, 0), BLACK));
    assert(board->goban[to_pos(2, 0)] == BLACK);
    assert(board->goban[to_pos(1, 0)] == EMPTY);
    assert(board->captures[0] == 1);
    assert(!board_play(board, to_pos(1, 0), WHITE));

    board_free(board);
}


void test_board() {
    board_initialize();

    run_test(test_search);
    run_test(test_to_pos);
    run_test(test_has_libs_001);
    run_test(test_has_libs_002);
    run_test(test_has_libs_003);
    run_test(test_kill_group_001);
    run_test(test_kill_group_002);

    run_test(test_board_play_001);
    run_test(test_board_play_002_illegal);
    run_test(test_board_play_003_capture);
    run_test(test_board_play_004_ko);

    board_destroy();
}
