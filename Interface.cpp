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

    PnSearch pn;

    if(strcmp(input, "SOLVE_GAME_STATE") == 0) {
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

    board.destroy();

    return true;
}
