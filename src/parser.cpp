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

node_p Parser::parse(bool expr_only) {
    return expr_only ? expr() : program();
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
        case token_type::dbl:
            n = node_factory(node_type::double_lit, StaticTokensContainer(tokenizer.last_tokens.token_d));
            require_next(token_type::dbl);

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
        case token_type::id: {
            token<std::string> tok = tokenizer.last_tokens.token_s;
            require_next(token_type::id);
            n = node_factory(node_type::variable, StaticTokensContainer(tok));

            return n;
        }
        default:
            throw IncompleteFeature("Unknown token type " + std::to_string(t) + " in Parser::factor");
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

node_p Parser::variable() {
    token<std::string> tok = tokenizer.last_tokens.token_s;
    require_next(token_type::id);
    return node_factory(node_type::variable, tok);
}

node_p Parser::type_spec() {
    token<std::string> tok = tokenizer.last_tokens.token_s;
    require_next(tok.type);
    return node_factory(node_type::type_spec, StaticTokensContainer(tok));
}

node_p Parser::var_decl() {
    node_p var_node = variable();
    require_next(token_type::colon);
    node_p type_node = type_spec();
    node_p value_node = null_node();

    if (get_token_type(tokenizer.last_tokens) == token_type::assign) {
        require_next(token_type::assign);
        value_node = expr();
    }

    require_next(token_type::semi);

    return var_decl_factory(std::move(var_node), std::move(type_node), std::move(value_node));
}

node_p Parser::stmt() {
    switch (get_token_type(tokenizer.last_tokens)) {
        case token_type::keyword: {
            std::string kw = tokenizer.last_tokens.token_s.value;
            require_next(token_type::keyword);
            if (kw == "var") {
                return var_decl();
            } else {
                throw ShouldNotReach("Parser::stmt kw");
            }
        }
        default:
            node_p n = expr();
            if (n) require_next(token_type::semi);

            return n;
    }
}

std::vector<node_p> Parser::stmt_list() {
    std::vector<node_p> stmts;

    node_p n = stmt();
    if (!n) return stmts;
    else stmts.push_back(std::move(n));

    while (get_token_type(tokenizer.last_tokens) != token_type::null) {
        stmts.push_back(std::move(stmt()));
    }

    return stmts;
}

node_p Parser::program() {
    std::vector<node_p> stmts = stmt_list();

    if (stmts.size() == 0) return null_node();
    else return stmt_list_factory(node_type::program, std::move(stmts));
}
