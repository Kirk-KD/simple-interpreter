#ifndef TOKENIZER_H
#define TOKENIZER_H

#define NULL_CHAR '\0'

#include <vector>
#include <string>

#include "token.h"
#include "tokens_container.h"
#include "exception.h"

inline bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

inline bool is_digit(char c) {
    return c >= 48 && c <= 57;
}

inline bool is_alpha(char c) {
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

struct make_int_result {
    int int_res;
    float float_res;
    bool is_int;
};

class Tokenizer {
    std::string code;
    int code_length;

    int position = -1;
    char current_char = NULL_CHAR;

    void advance();

    void skip_whitespace();

    make_int_result make_int();

    std::string make_id();
public:
    TokensContainer last_tokens;

    Tokenizer(std::string code);

    ~Tokenizer();

    void next_token();
};

#endif
