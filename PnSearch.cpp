#include "PnSearch.hpp"

bool PnSearch::canPlayerWin(Board* board, int player) {
    // TODO: check if this is correct
    playerToCheck = player;
    numberOfNodes = 1;

    Node* root = (Node*)malloc(sizeof(Node));
    // printf("CHECK: %d\n", player);
    // printf("TURN: %d\n", board->player);
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

    //TODO: delete startBoard
    startBoard = (Board*)malloc(sizeof(Board));
    startBoard->copy_from(*board);

    travelsardBoard = (Board*)malloc(sizeof(Board));
    travelsardBoard->copy_from(*board);

    solver = (Solver*)malloc(sizeof(Solver));

    PN(root, MAX_NODES);

    bool can_win = root->proof == 0;

    destroy(root);

    startBoard->destroy();
    free(startBoard);
    
    travelsardBoard->destroy();
    free(travelsardBoard);

    free(solver);

    return can_win;
}

void PnSearch::PN(Node* root, int maxnodes) {
    evaluate(root, travelsardBoard);
    setProofAndDisproofNumbers(root);

    Node* currentNode = root;

    pn_deb {
        printf("START BOARD:\n");
        travelsardBoard->print();
        printf("PLAYER: %d\n\n", travelsardBoard->player);
    }

    trav_deb {
        printf("START BOARD:\n");
        travelsardBoard->print();
        printf("PLAYER: %d\n\n", travelsardBoard->player);
    }

    while(root->proof != 0 && root->disproof != 0 && countNodes() <= maxnodes) {
        Node* mpn = selectMostProvingNode(currentNode);

        expandNode(mpn);

        pn_deb {
            printf("NEW BOARD I:\n");
            travelsardBoard->print();
            printf("\n");
        }

        currentNode = updateAncestors(mpn, root);

        pn_deb {
            printf("NEW BOARD II:\n");
            travelsardBoard->print();
            printf("\n");
        }
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
    trav_deb {
        printf("EVALUATING BOARD:\n");
        board->print();
        printf("WINNER: %d\n\n", winner);
    }
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
        trav_deb {
            printf("GO DOWN %d:\n", i);
            travelsardBoard->print();
            printf("PLAYER: %d\n\n", travelsardBoard->player);
        }
    }
    return node;
}

void PnSearch::expandNode(Node* node) {
    generateAllChildren(node);

    // pn_deb {
    //     printf("EXPANDED NODE:\n");
    //     node->print();
    // }
    pn_deb printf("\n");

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
            pn_deb printf("NUMBER OF NODES: %d\n\n", numberOfNodes);
        }

        if(node == root) {
            return node;
        }

        node = node->parent;
        travelsardBoard->undo_move();
        travelsardBoard->next_player();
        trav_deb {
            printf("GO UP:\n");
            travelsardBoard->print();
            printf("PLAYER: %d\n\n", travelsardBoard->player);
        }

    } while(true);
}

void PnSearch::generateAllChildren(Node* node) {
    solver->save_all_pos_mov_cut_if_game_over(*travelsardBoard);
    node->number_of_children = solver->board_count;

    pn_deb printf("NUMBER OF CHILDREN: %d\n", node->number_of_children);

    if(node->number_of_children == 0) {
        node->children = NULL;
        return;
    }

    // allocate memory for children and set start values
    node->children = (Node**)malloc(sizeof(Node*) * node->number_of_children);
    // pn_deb printf("ALLOCATION: %p\n", node->children);
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
    pn_deb printf("NUMBER OF NODES: %d\n\n", numberOfNodes);
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
