#include "parser.h"

Parser::Parser(std::string code) : tokenizer(Tokenizer(code)) {

}

Parser::~Parser() {}
