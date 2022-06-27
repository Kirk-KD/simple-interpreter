#ifndef TOKEN_H
#define TOKEN_H

enum token_type {
    integer,    // 0
    floating,
    decimal,

    plus,       // 3
    minus,
    multiply,   
    divide,
    round_l,
    round_r,

    id,         // 9
    null,
    
    error_token = -1
};

enum value_type {
    null_t,
    int_t,
    float_t,
    double_t,
    string_t
};

template<typename T>
struct token
{
    token_type type;
    T value;
};

#endif
