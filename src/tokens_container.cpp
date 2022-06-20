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
 * @param token token
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

/**
 * Converts the value of the latest token to string for logging
 * purposes.
 * 
 * @return The value of a token, converted to string.
 */
std::string TokensContainer::to_string() {
    switch (val_type) {
        case value_type::int_t:
            return std::to_string(token_i.value);
        case value_type::float_t:
            return std::to_string(token_f.value);
        case value_type::string_t:
            return token_s.value;
        case value_type::null_t:
            return "NULL";
        default:
            return "Error";
    }
}
