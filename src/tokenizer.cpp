#include "tokenizer.h"

Tokenizer::Tokenizer(std::string c) {
    code = c;
    code_lenght = sizeof(c);

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
 * Outputs the next token to locations of various token types based on
 * the type of the token value generated.
 * 
 * @param token_i Integer value token.
 * @param token_f Float value token.
 * @param token_s String value token.
 * @param token_c Char value token.
 * 
 * @return An enum of the type of the token value.
 */
value_type Tokenizer::next_token(
    token<int> &token_i,
    token<float> &token_f,
    token<std::string> &token_s,
    token<char> &token_c
) {
    while (current_char != NULL_CHAR) {
        if (is_whitespace(current_char)) {
            skip_whitespace();
            continue;
        } else if (is_digit(current_char)) {
            token_i = token<int>{token_type::integer, make_int()};
            return value_type::int_t;
        } else if (is_alpha(current_char) || current_char == '_') {
            token_s = token<std::string>{token_type::id, make_id()};
            return value_type::string_t;
        }
    }

    return value_type::null_t;
}
