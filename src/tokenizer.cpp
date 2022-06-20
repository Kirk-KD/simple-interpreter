#include "tokenizer.h"

Tokenizer::Tokenizer(std::string c) {
    code = c;
    code_lenght = c.size();

    advance();
}

Tokenizer::~Tokenizer() {}

/**
 * Increment `position` by one and set `current_char` to the character
 * at `position` if `position` is in range. Otherwise set `current_char`
 * to NULL_CHAR.
 */
void Tokenizer::advance() {
    if (position + 1 < code_lenght) {
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
int Tokenizer::make_int() {
    std::string res;
    while (current_char != NULL_CHAR && is_digit(current_char)) {
        res += current_char;
        advance();
    }
    return std::stoi(res);
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
            last_tokens.set_token(token<int>{token_type::integer, make_int()});
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
                    tt = token_type::error;
                    break;
            }
            last_tokens.set_token(token<std::string>{tt, std::string{current_char}});
            advance();
            return;
        }
    }

    last_tokens.set_null();
}
