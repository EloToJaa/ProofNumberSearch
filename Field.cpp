#include "Field.hpp"


void Field::init(int x, int y, int value) {
    this->x = x;
    this->y = y;
    this->value = value;    
}

void Field::set_value(int value) {
    this->value = value;
}

int Field::get_value() {
    return this->value;
}
