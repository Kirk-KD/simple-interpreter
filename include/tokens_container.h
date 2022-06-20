#ifndef TOKENS_CONTAINER_H
#define TOKENS_CONTAINER_H

#include <string>

#include "token.h"

class TokensContainer {
public:
    value_type val_type;
    token<int> token_i;
    token<float> token_f;
    token<std::string> token_s;

    TokensContainer();

    ~TokensContainer();

    void set_token(token<int> token);

    void set_token(token<float> token);

    void set_token(token<std::string> token);

    void set_null();

    token_type get_token_type();

    std::string to_string();
};

#endif