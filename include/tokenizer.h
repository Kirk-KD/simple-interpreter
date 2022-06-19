#ifndef TOKENIZER_H
#define TOKENIZER_H

#define NULL_CHAR '\0'

#include <vector>
#include <string>

#include "token.h"

inline bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

inline bool is_digit(char c) {
    return c >= 48 && c <= 57;
}

inline bool is_alpha(char c) {
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

class Tokenizer {
    std::string code;
    int code_lenght;

    int position = -1;
    char current_char = NULL_CHAR;

    void advance();

    void skip_whitespace();

    int make_int();

    std::string make_id();
public:
    Tokenizer(std::string code);

    ~Tokenizer();

    value_type next_token(
        token<int> &token_i,
        token<float> &token_f,
        token<std::string> &token_s,
        token<char> &token_c
    );
};

#endif
