#include "PnSearch.hpp"

bool PnSearch::canPlayerWin(Board* board, int player) {
    playerToCheck = player;
    numberOfNodes = 1;

    Node* root = (Node*)malloc(sizeof(Node));
    if(board->player == WHITE) {
        if(player == WHITE) {
            root->type = OR_NODE;
        }
        else if (player == BLACK) {
            root->type = AND_NODE;
        }
    }
    else if(board->player == BLACK) {
        if(player == WHITE) {
            root->type = AND_NODE;
        }
        else if (player == BLACK) {
            root->type = OR_NODE;
        }
    }
    root->expanded = false;
    root->number_of_children = 0;

    travelsardBoard = (Board*)malloc(sizeof(Board));
    travelsardBoard->copy_from(*board);

    solver = (Solver*)malloc(sizeof(Solver));

    PN(root, MAX_NODES);

    bool can_win = root->proof == 0;

    destroy(root);
    
    travelsardBoard->destroy();
    free(travelsardBoard);

    free(solver);

    return can_win;
}

void PnSearch::PN(Node* root, int maxnodes) {
    evaluate(root, travelsardBoard);
    setProofAndDisproofNumbers(root);

    Node* currentNode = root;

    while(root->proof != 0 && root->disproof != 0 && countNodes() <= maxnodes) {
        Node* mpn = selectMostProvingNode(currentNode);

        expandNode(mpn);

        currentNode = updateAncestors(mpn, root);
    }
    if(root->proof == 0) {
        root->value = TRUE;
    }
    else if(root->disproof == 0) {
        root->value = FALSE;
    }
    else {
        root->value = UNKNOWN;
    }
}

void PnSearch::evaluate(Node* node, Board* board) {
    int winner = board->get_winner();
    if (winner == NONE) {
        if(board->empty_count == 0) {
            node->value = FALSE;
        }
        else {
            node->value = UNKNOWN;
        }
    } else if(winner == playerToCheck) {
        node->value = TRUE;
    } else {
        node->value = FALSE;
    }
}

void PnSearch::setProofAndDisproofNumbers(Node* node) {
    if(node->expanded) {
        if(node->type == AND_NODE) {
            node->proof = 0;
            node->disproof = INFINITY;
            FOR(i, node->number_of_children) {
                node->proof = node->proof + node->children[i]->proof;
                if(node->children[i]->disproof < node->disproof) {
                    node->disproof = node->children[i]->disproof;
                }
            }
        } else if(node->type == OR_NODE) {
            node->proof = INFINITY;
            node->disproof = 0;
            FOR(i, node->number_of_children) {
                node->disproof = node->disproof + node->children[i]->disproof;
                if(node->children[i]->proof < node->proof) {
                    node->proof = node->children[i]->proof;
                }
            }
        }
    }
    else {
        switch(node->value) {
            case FALSE:
                node->proof = INFINITY;
                node->disproof = 0;
                break;
            case TRUE:
                node->proof = 0;
                node->disproof = INFINITY;
                break;
            case UNKNOWN:
                node->proof = 1;
                node->disproof = 1;
                break;
        }
    }
}

int PnSearch::countNodes() {
    return numberOfNodes;
}

Node* PnSearch::selectMostProvingNode(Node* node) {
    int i;
    while(node->expanded) {
        i = 0;

        if(node->type == OR_NODE) {
            while(node->children[i]->proof != node->proof) {
                i++;
            }
        } else if(node->type == AND_NODE) {
            while(node->children[i]->disproof != node->disproof) {
                i++;
            }
        }

        node = node->children[i];
        travelsardBoard->kth_move(i);
        travelsardBoard->next_player();
    }
    return node;
}

void PnSearch::expandNode(Node* node) {
    generateAllChildren(node);

    FOR(i, node->number_of_children) {
        evaluate(node->children[i], &(solver->boards[i]));
        setProofAndDisproofNumbers(node->children[i]);
        if((node->type == OR_NODE && node->children[i]->proof == 0) || (node->type == AND_NODE && node->children[i]->disproof == 0)) {
            break;
        }
    }
    solver->destroy();
    node->expanded = true;
}

Node* PnSearch::updateAncestors(Node* node, Node* root) {
    do {
        ll oldProof = node->proof;
        ll oldDisproof = node->disproof;

        setProofAndDisproofNumbers(node);
        if(node->proof == 0) {
            node->value = TRUE;
        }
        else if(node->disproof == 0) {
            node->value = FALSE;
        }
        else {
            node->value = UNKNOWN;
        }

        if(node->proof == oldProof && node->disproof == oldDisproof) {
            return node;
        }

        if(node->proof == 0 || node->disproof == 0) {
            node->deleteSubtree();
            numberOfNodes -= node->deleted_nodes;
        }

        if(node == root) {
            return node;
        }

        node = node->parent;
        travelsardBoard->undo_move();
        travelsardBoard->next_player();

    } while(true);
}

void PnSearch::generateAllChildren(Node* node) {
    solver->save_all_pos_mov_cut_if_game_over(*travelsardBoard);
    node->number_of_children = solver->board_count;

    if(node->number_of_children == 0) {
        node->children = NULL;
        return;
    }

    // allocate memory for children and set start values
    node->children = (Node**)malloc(sizeof(Node*) * node->number_of_children);
    node->expanded = true;

    FOR(i, node->number_of_children) {
        node->children[i] = (Node*)malloc(sizeof(Node));
        setDefaultValues(node->children[i], node);
    }
    numberOfNodes += node->number_of_children;
}

void PnSearch::destroy(Node* root) {
    root->deleteSubtree();
    numberOfNodes -= root->deleted_nodes;
    free(root);
}

void PnSearch::setDefaultValues(Node* node, Node* parent) {
    node->parent = parent;
    node->type = !(parent->type);
    node->expanded = false;
    node->number_of_children = 0;
    node->children = NULL;
    node->proof = 1;
    node->disproof = 1;
}
