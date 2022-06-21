#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "ast.h"

class Parser {
    Tokenizer tokenizer;
    TokensContainer current_token;
public:
    Parser(std::string code);

    ~Parser();

    int require_next(token_type type);

    node_p parse();

    // Grammars
    node_p factor();

    node_p term();

    node_p expr();
};

#endif