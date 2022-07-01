#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "tokenizer.h"
#include "ast.h"
#include "exception.h"

class Parser {
    Tokenizer tokenizer;
public:
    Parser(std::string code);

    ~Parser();

    void require_next(token_type type);

    node_p parse(bool expr_only = false);

    // Grammars
    node_p factor();

    node_p term();

    node_p expr();

    node_p variable();

    node_p type_spec();

    node_p var_decl();
    
    node_p var_assign();

    node_p stmt();

    std::vector<node_p> stmt_list();

    node_p program();
};

#endif