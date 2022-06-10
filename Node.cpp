#include "Node.hpp"


void Node::deleteSubtree() {
    deleted_nodes = 0;
    deleteSubtreeUtil(this);
    deleted_nodes--;
}

void Node::deleteSubtreeUtil(Node* node) {
    FOR(i, node->number_of_children) {
        deleteSubtreeUtil(node->children[i]);
    }

    if(node->number_of_children > 0) free(node->children);
    
    node->number_of_children = 0;
    node->children = NULL;
    node->expanded = false;

    if(node != this) {
        free(node);
    }

    deleted_nodes++;
}
