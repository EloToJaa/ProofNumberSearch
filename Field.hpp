#pragma once

#include "Header.hpp"

struct Field {
private:
    int x;
    int y;
    int value;

public:
    void init(int x, int y, int value);
    void set_value(int value);
    int get_value();
};