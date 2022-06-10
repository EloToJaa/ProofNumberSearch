#pragma once

#include "Header.hpp"

struct Node {
    int value;
    ll proof;
    ll disproof;
    bool type;
    bool expanded;
    int deleted_nodes;
    int number_of_nodes;

    int number_of_children;
    Node** children;

    Node* parent;

    void deleteSubtree();
    void deleteSubtreeUtil(Node* node);
    void print();
    void printUtil(Node* node);
    void printValues(Node* node);
};