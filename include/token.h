#ifndef TOKEN_H
#define TOKEN_H

enum token_type {
    integer,
    plus,
    minus,
    multiply,
    devide,
    round_l,
    round_r,
    id
};

enum value_type {
    null_t,
    int_t,
    float_t,
    string_t
};

template <typename T>
struct token
{
    token_type type;
    T value;
};

#endif
