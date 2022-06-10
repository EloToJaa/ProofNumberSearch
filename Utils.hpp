#pragma once

#include "Header.hpp"

struct Utils {
    void zero_calc_board(int **calc, int n, int m);
    void destroy_calc_board(int **calc, int n);
    void print_calc_board(int **calc, int n, int m);
};