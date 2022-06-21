#include "tokens_container.h"

TokensContainer::TokensContainer() {}

TokensContainer::~TokensContainer() {}

/**
 * Sets a token of type int.
 * 
 * @param token token
 */
void TokensContainer::set_token(token<int> token) {
    token_i = token;
    val_type = value_type::int_t;
}

/**
 * Sets a token of type float.
 * 
 * @param token token
 */
void TokensContainer::set_token(token<float> token) {
    token_f = token;
    val_type = value_type::float_t;
}

/**
 * Sets a token of type string.
 * 
 * @param token Token
 */
void TokensContainer::set_token(token<std::string> token) {
    token_s = token;
    val_type = value_type::string_t;
}

/**
 * Sets `val_type` to `value_type::null_t` to indicate that an error
 * occured or the tokenizer is done reading.
 */
void TokensContainer::set_null() {
    val_type = value_type::null_t;
}

// StaticTokensContainer is used when a token with multiple possible
// types occures, but will not change its value.

StaticTokensContainer::StaticTokensContainer() {
    val_type = value_type::null_t;
}

StaticTokensContainer::StaticTokensContainer(token<int> tok) {
    val_type = value_type::int_t;
    token_i = tok;
}

StaticTokensContainer::StaticTokensContainer(token<float> tok) {
    val_type = value_type::float_t;
    token_f = tok;
}

StaticTokensContainer::StaticTokensContainer(token<std::string> tok) {
    val_type = value_type::string_t;
    token_s = tok;
}

StaticTokensContainer::~StaticTokensContainer() {}

/**
 * Gets the latest token type of a TokensContainer.
 * 
 * @param tok TokensContainer
 * @return The latest token's type.
 */
token_type get_token_type(TokensContainer tok) {
    switch (tok.val_type) {
        case value_type::int_t:
            return tok.token_i.type;
        case value_type::float_t:
            return tok.token_f.type;
        case value_type::string_t:
            return tok.token_s.type;
        case value_type::null_t:
            return token_type::null;
        default:
            return token_type::error;
    }
}

/**
 * Gets the latest token type of a StaticTokensContainer.
 * 
 * @param tok StaticTokensContainer
 * @return The latest token's type.
 */
token_type get_token_type(StaticTokensContainer tok) {
    switch (tok.val_type) {
        case value_type::int_t:
            return tok.token_i.type;
        case value_type::float_t:
            return tok.token_f.type;
        case value_type::string_t:
            return tok.token_s.type;
        case value_type::null_t:
            return token_type::null;
        default:
            return token_type::error;
    }
}

/**
 * Converts the value of the latest token of a TokensContainer to
 * string for logging purposes.
 * 
 * @param tok TokensContainer
 * @return The value of a token, converted to string.
 */
std::string value_to_string(TokensContainer tok) {
    switch (tok.val_type) {
        case value_type::int_t:
            return std::to_string(tok.token_i.value);
        case value_type::float_t:
            return std::to_string(tok.token_f.value);
        case value_type::string_t:
            return tok.token_s.value;
        case value_type::null_t:
            return "NULL";
        default:
            return "Error";
    }
}

/**
 * Converts the value of the latest token of a StaticTokensContainer to
 * string for logging purposes.
 * 
 * @param tok StaticTokensContainer
 * @return The value of a token, converted to string.
 */
std::string value_to_string(StaticTokensContainer tok) {
    switch (tok.val_type) {
        case value_type::int_t:
            return std::to_string(tok.token_i.value);
        case value_type::float_t:
            return std::to_string(tok.token_f.value);
        case value_type::string_t:
            return tok.token_s.value;
        case value_type::null_t:
            return "NULL";
        default:
            return "Error";
    }
}
