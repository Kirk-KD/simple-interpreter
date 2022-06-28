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
make_num_result Tokenizer::make_num() {
    std::string res;
    num_type type = num_type::int_res;
    while (current_char != NULL_CHAR && (is_digit(current_char) || current_char == '.' || current_char == 'd')) {
        if (current_char == '.') {
            if (type == num_type::int_res) type = num_type::float_res;
            else break;
        } else if (current_char == 'd') {
            type = num_type::double_res;
            advance();
            break;
        }
        res += current_char;
        advance();
    }
    switch (type) {
        case num_type::int_res:
            return make_num_result{std::stoi(res), 0, 0, type};
        case num_type::float_res:
            return make_num_result{0, std::stof(res), 0, type};
        case num_type::double_res:
            return make_num_result{0, 0, std::stod(res), type};
        default:
            throw ShouldNotReach("make_num");
    }
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
            make_num_result res = make_num();
            switch (res.type) {
                case num_type::int_res:
                    last_tokens.set_token(token<int>{token_type::integer, res.int_res});
                    break;
                case num_type::float_res:
                    last_tokens.set_token(token<float>{token_type::floating, res.float_res});
                    break;
                case num_type::double_res:
                    last_tokens.set_token(token<double>{token_type::decimal, res.double_res});
                    break;
            }
            return;
        // } else if (is_alpha(current_char) || current_char == '_') {
        //     last_tokens.set_token(token<std::string>{token_type::id, make_id()});
        //     return;
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
                case ';':
                    tt = token_type::semi;
                    break;
                default:
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
