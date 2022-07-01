#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>

#include "tokens_container.h"

enum node_type {
    int_lit,        // 0
    float_lit,
    double_lit,

    bin_op,         // 3
    una_op,

    variable,       // 5
    var_decl,
    var_assign,
    type_spec,

    program,        // 9

    error_node      = -1
};

struct node {
    node_type type;

    StaticTokensContainer token_sc = StaticTokensContainer();
    std::unique_ptr<node> left = std::unique_ptr<node>{};
    std::unique_ptr<node> right = std::unique_ptr<node>{};

    // For stmt_list
    std::vector<std::unique_ptr<node>> children = std::vector<std::unique_ptr<node>>();

    // Special properties of var_decl
    std::unique_ptr<node> var_node = std::unique_ptr<node>{};
    std::unique_ptr<node> type_node = std::unique_ptr<node>{};
    std::unique_ptr<node> value_node = std::unique_ptr<node>{};
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

node_p var_decl_factory(
    std::unique_ptr<node> var_node,
    std::unique_ptr<node> type_node,
    std::unique_ptr<node> value_node
);

node_p stmt_list_factory(
    node_type type,
    std::vector<node_p> children
);

std::string node_to_string(const node& n);

#endif