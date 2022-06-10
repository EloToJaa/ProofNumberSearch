#pragma once

#include "Header.hpp"

struct Board {
    int n, m, k;
    Field **fields;

    int saved_moves_count;
    int* saved_moves;

    int player;
    int winner;

    int black_count;
    int white_count;
    int empty_count;
    int start_depth;

    bool win_check(int player);
    bool on_board(int x, int y);
    void set_default_values();

    void set_field(int x, int y, int value);
    int get_field(int x, int y);
    void swap_fields(int x, int y, int dx, int dy);

    void kth_zero(int& rx, int& ry, int x, int y, int k);
    void next(int& rx, int& ry, int x, int y, int k);

    void copy_from(Board& board);
    void init(int n, int m, int k, int player);
    void destroy();

    void print();
    
    int get_winner();

    void next_player();
    void kth_move(int k);
    void undo_move();
};