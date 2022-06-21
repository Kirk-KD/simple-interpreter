#include "parser.h"

Parser::Parser(std::string code) : tokenizer(Tokenizer(code)) {
    tokenizer.next_token();
}

Parser::~Parser() {}

int Parser::require_next(token_type type) {
    tokenizer.next_token();

    token_type t = get_token_type(tokenizer.last_tokens);
    return t == type;
}

node_p Parser::parse() {
    return factor();
}

// Grammars
node_p Parser::factor() {
    node_p n = null_node();

    switch (get_token_type(tokenizer.last_tokens)) {
        case token_type::integer:
            n = node_factory(node_type::int_lit, StaticTokensContainer(tokenizer.last_tokens.token_i), null_node(), null_node());
            require_next(token_type::integer);
            return n;
        default:
            return null_node();
    }
}
