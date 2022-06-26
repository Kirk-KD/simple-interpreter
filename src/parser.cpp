#include "parser.h"

Parser::Parser(std::string code) : tokenizer(Tokenizer(code)) {
    tokenizer.next_token();
}

Parser::~Parser() {}

void Parser::require_next(token_type type) {
    token_type t = get_token_type(tokenizer.last_tokens);
    tokenizer.next_token();
    if (t != type) throw UnexpectedToken(t, type);
}

node_p Parser::parse() {
    return expr();
}

// grammars.txt
node_p Parser::factor() {
    node_p n = null_node();

    token_type t = get_token_type(tokenizer.last_tokens);
    switch (t) {
        case token_type::integer:
            n = node_factory(node_type::int_lit, StaticTokensContainer(tokenizer.last_tokens.token_i));
            require_next(token_type::integer);

            return n;
        case token_type::floating:
            n = node_factory(node_type::float_lit, StaticTokensContainer(tokenizer.last_tokens.token_f));
            require_next(token_type::floating);

            return n;
        case token_type::plus:
        case token_type::minus: {
            token<std::string> tok = tokenizer.last_tokens.token_s;
            require_next(t);
            n = node_factory(node_type::una_op, StaticTokensContainer(tok), null_node(), factor());

            return n;
        }
        case token_type::round_l:
            require_next(token_type::round_l);
            n = expr();
            require_next(token_type::round_r);
            
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
