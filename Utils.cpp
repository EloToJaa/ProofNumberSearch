#include "Utils.hpp"


void Utils::zero_calc_board(int **calc, int n, int m) {
    FOR(i, n) {
        FOR(j, m) {
            calc[i][j] = 0;
        }
    }    
}

void Utils::destroy_calc_board(int **calc, int n) {
    FOR(i, n) {
        free(calc[i]);
    }
    free(calc);
}

void Utils::print_calc_board(int **calc, int n, int m) {
    FOR(i, n) {
        FOR(j, m) {
            printf("%d ", calc[i][j]);
        }
        printf("\n");
    }
    win_deb printf("\n");
}
