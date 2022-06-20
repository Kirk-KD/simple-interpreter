#ifndef TOKEN_H
#define TOKEN_H

enum token_type {
    integer,
    plus,
    minus,
    multiply,
    divide, // I was a dumbass that spelled divide "devide", shame on me.
    round_l,
    round_r,
    id,
    null,
    
    error = -1
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
