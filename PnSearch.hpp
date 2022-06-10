#pragma once

#include "Header.hpp"

struct PnSearch {
    int playerToCheck;
    Solver* solver;
    Board *travelsardBoard;
    int numberOfNodes;

    // can player "player" win?
    bool canPlayerWin(Board* board, int player);
    // Proof Number Search
    void PN(Node* root, int maxnodes);
    // Board evaluation
    void evaluate(Node* node, Board* board);
    // set proof and disproof numbers
    void setProofAndDisproofNumbers(Node* node);
    // return number of nodes
    int countNodes();
    // select most proving node from all children
    Node* selectMostProvingNode(Node* node);
    // expand node by adding children
    void expandNode(Node* node);
    // backpropagate to update ancestors
    Node* updateAncestors(Node* node, Node* root);
    // generate all children using the Solver
    void generateAllChildren(Node* node);
    // set default values for node
    void setDefaultValues(Node* node, Node* parent);
    // free memory and destroy the object
    void destroy(Node* root);
};