#pragma once

#include "Header.hpp"

struct Solver {
public:
    Board *boards;
    int board_count;
    int winner;

    void save_all_pos_mov(Board& board);
    void save_all_pos_mov_cut_if_game_over(Board& board);
    void gen_all_pos_mov(Board& board);
    void gen_all_pos_mov_cut_if_game_over(Board& board);
    void print_all_pos_mov();
    Board get_pos_mov(int k);
    void print_pos_mov(int k);
    void destroy();
};