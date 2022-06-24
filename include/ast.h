#ifndef AST_H
#define AST_H

#include <memory>

#include "tokens_container.h"

enum node_type {
    int_lit,
    float_lit,
    bin_op,

    error_node = -1
};

struct node {
    node_type type;
    StaticTokensContainer token_sc;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
};

typedef std::unique_ptr<node> node_p;

node_p null_node();

node_p err_node();

node_p node_factory(
    node_type type,
    StaticTokensContainer token_sc = StaticTokensContainer(),
    node_p left = null_node(),
    node_p right = null_node()
);

std::string node_to_string(const node& n);

#endif