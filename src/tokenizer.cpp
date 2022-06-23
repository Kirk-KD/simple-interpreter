#include "tokenizer.h"

Tokenizer::Tokenizer(std::string c) {
    code = c;
    code_length = c.size();

    advance();
}

Tokenizer::~Tokenizer() {}

/**
 * Increment `position` by one and set `current_char` to the character
 * at `position` if `position` is in range. Otherwise set `current_char`
 * to NULL_CHAR.
 */
void Tokenizer::advance() {
    if (position + 1 < code_length) {
        ++position;
        current_char = code[position];
    } else {
        current_char = NULL_CHAR;
    }
}

/**
 * Skips whitespaces.
 */
void Tokenizer::skip_whitespace() {
    while (is_whitespace(current_char)) {
        advance();
    }
}

/**
 * Makes an integer starting from the current character.
 */
make_int_result Tokenizer::make_int() {
    std::string res;
    bool is_int = true;
    while (current_char != NULL_CHAR && (is_digit(current_char) || current_char == '.')) {
        if (current_char == '.') {
            if (is_int) is_int = false;
            else break;
        }
        res += current_char;
        advance();
    }
    if (is_int) return make_int_result{std::stoi(res), 0, is_int};
    else return make_int_result{0, std::stof(res), is_int};
}

/**
 * Makes an id starting from the current character.
 */
std::string Tokenizer::make_id() {
    std::string res;
    while (current_char != NULL_CHAR && (is_alpha(current_char) || is_digit(current_char) || current_char == '_')) {
        res += current_char;
        advance();
    }
    return res;
}

/**
 * Read from `code` and write the token generated to the corresponding
 * token type in `last_tokens`, along with the token value type.
 */
void Tokenizer::next_token() {
    while (current_char != NULL_CHAR) {
        if (is_whitespace(current_char)) {
            skip_whitespace();
            continue;
        } else if (is_digit(current_char)) {
            make_int_result res = make_int();
            if (res.is_int) last_tokens.set_token(token<int>{token_type::integer, res.int_res});
            else last_tokens.set_token(token<float>{token_type::floating, res.float_res});
            return;
        } else if (is_alpha(current_char) || current_char == '_') {
            last_tokens.set_token(token<std::string>{token_type::id, make_id()});
            return;
        } else { // single character operators
            token_type tt;
            switch (current_char) {
                case '+':
                    tt = token_type::plus;
                    break;
                case '-':
                    tt = token_type::minus;
                    break;
                case '*':
                    tt = token_type::multiply;
                    break;
                case '/':
                    tt = token_type::divide;
                    break;
                case '(':
                    tt = token_type::round_l;
                    break;
                case ')':
                    tt = token_type::round_r;
                    break;
                default:
                    tt = token_type::error_token;

                    throw UnexpectedCharacter(current_char, position);
                    break;
            }
            last_tokens.set_token(token<std::string>{tt, std::string{current_char}});
            advance();
            return;
        }
    }

    last_tokens.set_null();
}
