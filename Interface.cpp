#include "Interface.hpp"


void Interface::handler() {
    while (true) {
        if(!handle_input()) break;
    }    
}

bool Interface::handle_input() {
    char input[40];
    int n, m, k, player;

    if(scanf("%s", input) == EOF) return false;
    scanf("%d %d %d %d", &n, &m, &k, &player);

    Board board;
    board.init(n, m, k, player);

    FOR(i, n) {
        FOR(j, m) {
            int value;
            scanf("%d", &value);
            board.set_field(i, j, value);
        }
    }

    deb {
        printf("STARTING BOARD:\n");
        board.print();
        printf("\n");
    }

    Solver solver;
    PnSearch pn;

    if(strcmp(input, "GEN_ALL_POS_MOV") == 0) {
        solver.gen_all_pos_mov(board);
        solver.destroy();
    }
    else if(strcmp(input, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) {
        solver.gen_all_pos_mov_cut_if_game_over(board);
        solver.destroy();
    }
    else if(strcmp(input, "SOLVE_GAME_STATE") == 0) {
        if(pn.canPlayerWin(&board, WHITE)) {
            printf("FIRST_PLAYER_WINS\n");
        }
        else if(pn.canPlayerWin(&board, BLACK)) {
            printf("SECOND_PLAYER_WINS\n");
        }
        else {
            printf("BOTH_PLAYERS_TIE\n");
        }
    }
    else if(strcmp(input, "TEST") == 0) {
        int rx, ry;
        FOR(i, board.empty_count) {
            board.kth_zero(rx, ry, 0, 0, i);
            printf("%d: %d %d\n", i, rx, ry);
        }
        printf("\n");
    }

    board.destroy();

    deb printf("\n");

    return true;
}
