#include "parser.h"

Parser::Parser(std::string code) : tokenizer(Tokenizer(code)) {
    tokenizer.next_token();
}

Parser::~Parser() {}

bool Parser::require_next(token_type type) {
    token_type t = get_token_type(tokenizer.last_tokens);
    tokenizer.next_token();
    return t == type;
}

node_p Parser::parse() {
    return expr();
}

// Grammars
node_p Parser::factor() {
    node_p n = null_node();

    switch (get_token_type(tokenizer.last_tokens)) {
        case token_type::integer:
            n = node_factory(node_type::int_lit, StaticTokensContainer(tokenizer.last_tokens.token_i));
            require_next(token_type::integer);

            return n;
        default:
            return null_node();
    }
}

node_p Parser::term() {
    node_p n = factor();
    token_type tt = get_token_type(tokenizer.last_tokens);

    while (tt == token_type::multiply || tt == token_type::divide) {
        token<std::string> tok = tokenizer.last_tokens.token_s;

        require_next(tok.type);

        node_p n_temp = node_factory(node_type::bin_op, StaticTokensContainer(tok), std::move(n), factor());
        n = std::move(n_temp);

        tt = get_token_type(tokenizer.last_tokens);
    }

    return n;
}

node_p Parser::expr() {
    node_p n = term();
    token_type tt = get_token_type(tokenizer.last_tokens);

    while (tt == token_type::plus || tt == token_type::minus) {
        token<std::string> tok = tokenizer.last_tokens.token_s;
        require_next(tok.type);

        node_p n_temp = node_factory(node_type::bin_op, StaticTokensContainer(tok), std::move(n), term());
        n = std::move(n_temp);

        tt = get_token_type(tokenizer.last_tokens);
    }

    return n;
}
