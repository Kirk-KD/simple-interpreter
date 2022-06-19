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
    token<char> token_c;

    std::string val_to_string();
};

#endif