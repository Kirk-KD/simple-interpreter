#include "tokens_container.h"

std::string TokensContainer::val_to_string() {
    switch (val_type) {
        case value_type::int_t:
            return std::to_string(token_i.value);
        case value_type::float_t:
            return std::to_string(token_f.value);
        case value_type::char_t:
            return std::string{token_c.value};
        case value_type::string_t:
            return token_s.value;
        case value_type::null_t:
            return "NULL";
        default:
            return "Error";
    }
}
