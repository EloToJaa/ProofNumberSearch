#include "Node.hpp"


void Node::deleteSubtree() {
    print();

    pn_deb printf("deleteSubtree()\n");
    deleted_nodes = 0;
    deleteSubtreeUtil(this);
    deleted_nodes--;
    pn_deb printf("deleted_nodes: %d\n", deleted_nodes);
}

void Node::deleteSubtreeUtil(Node* node) {
    // if(node == NULL || node->children == NULL || !expanded) {
    //     return;
    // }
    // pn_deb printf("PTR: %p\n", node->children);
    FOR(i, node->number_of_children) {
        deleteSubtreeUtil(node->children[i]);
    }

    // assert(node == this);
    if(node->number_of_children > 0) free(node->children);
    
    node->number_of_children = 0;
    node->children = NULL;
    node->expanded = false;

    if(node != this) {
        free(node);
    }

    deleted_nodes++;
}

void Node::print() {
    pn_deb printf("printSubtree()\n");
    trav_deb printf("printSubtree()\n");
    number_of_nodes = 0;
    printUtil(this);
    pn_deb printf("\n");
    trav_deb printf("\n");
}

void Node::printUtil(Node* node) {
    if(node == NULL) {
        return;
    }
    number_of_nodes++;
    pn_deb printf("%p\n", node->children);
    trav_deb {
        printValues(node);
    }
    FOR(i, node->number_of_children) {
        printUtil(node->children[i]);
    }
}

void Node::printValues(Node* node) {
    printf("PTR %p:\n", node);
    printf("proof: %lld\n", node->proof);
    printf("disproof: %lld\n", node->disproof);
    printf("value: %d\n\n", node->value);
}
