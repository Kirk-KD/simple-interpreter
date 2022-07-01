#ifndef TOKEN_H
#define TOKEN_H

enum token_type {
    integer,        // 0
    floating,
    dbl,

    int_type,       // 3
    float_type,
    double_type,

    plus,           // 6
    minus,
    multiply,
    divide,
    round_l,
    round_r,
    assign,

    semi,
    colon,

    id,
    keyword,
    null,

    error_token     = -1
};

enum value_type {
    int_t,
    float_t,
    double_t,
    string_t,
    null_t
};

template<typename T>
struct token
{
    token_type type;
    T value;
};

#endif
