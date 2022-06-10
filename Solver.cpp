#include "Solver.hpp"

void Solver::destroy() {
    // Clear all memory
    if(board_count == 0) return;
    FOR(i, board_count) {
        boards[i].destroy();
    }
    free(boards);
    board_count = 0;
}

void Solver::save_all_pos_mov(Board& board) {
    if(board.get_winner() != 0) {
        board_count = 0;
        return;
    }

    int n = board.empty_count;

    if(n == 0) {
        board_count = 0;
        return;
    }

    boards = (Board*)malloc(sizeof(Board) * n);
    board_count = n;

    Board board_copy;
    board_copy.copy_from(board);

    int x, y;
    bool b = false;
    FOR(i, board_copy.n) {
        FOR(j, board_copy.m) {
            if(board_copy.fields[i][j].get_value() == 0) {
                board_copy.set_field(i, j, board_copy.player);
                x = i;
                y = j;
                b = true;
                break;
            }
        }
        if(b) break;
    }

    boards[0].copy_from(board_copy);
    boards[0].next_player();

    int px = x, py = y;
    FOR(k, n - 1) {
        int i = k + 1;
        board_copy.kth_zero(x, y, x, y, 0);

        board_copy.swap_fields(px, py, x, y);
        boards[i].copy_from(board_copy);
        boards[i].next_player();

        px = x;
        py = y;
    }

    board_copy.destroy();
}

Board Solver::get_pos_mov(int k) {
    return boards[k];
}

void Solver::save_all_pos_mov_cut_if_game_over(Board& board) {
    int winner = board.get_winner();
    this->winner = winner;
    if(winner != 0) {
        board_count = 0;
        return;
    }

    save_all_pos_mov(board);
    
    int win_pos = -1;
    FOR(i, board_count) {
        if (boards[i].get_winner() != 0) {
            win_pos = i;
            break;
        }
    }

    if (win_pos != -1) {
        Board win_board;
        win_board.copy_from(boards[win_pos]);
        destroy();

        board_count = 1;
        boards = (Board*)malloc(sizeof(Board));
        boards[0].copy_from(win_board);

        win_board.destroy();
    }
}

