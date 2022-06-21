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
};

class StaticTokensContainer {
public:
    value_type val_type;
    token<int> token_i;
    token<float> token_f;
    token<std::string> token_s;

    StaticTokensContainer();

    StaticTokensContainer(token<int> tok);
    
    StaticTokensContainer(token<float> tok);
    
    StaticTokensContainer(token<std::string> tok);

    ~StaticTokensContainer();
};

token_type get_token_type(TokensContainer tok);

token_type get_token_type(StaticTokensContainer tok);

std::string value_to_string(TokensContainer tok);

std::string value_to_string(StaticTokensContainer tok);

#endif