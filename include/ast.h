#ifndef AST_H
#define AST_H

#include <memory>

#include "tokens_container.h"

enum node_type {
    bin_op,
    int_lit
};

struct node {
    node_type type;
    StaticTokensContainer token_sc;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
};

typedef std::unique_ptr<node> node_p;

node_p node_factory(
    node_type type,
    StaticTokensContainer token_sc,
    node_p left,
    node_p right
);

node_p null_node();

std::string node_to_string(const node& n);

#endif