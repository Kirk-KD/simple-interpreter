#ifndef AST_H
#define AST_H

#include <memory>

#include "tokens_container.h"

enum node_type {
    bin_op
};

struct node {
    node_type type;
    StaticTokensContainer token_sc;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
};

#endif