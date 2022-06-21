#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "ast.h"

class Parser {
    Tokenizer tokenizer;

public:
    Parser(std::string code);

    ~Parser();
};

#endif