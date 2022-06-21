#include <iostream>

#include "tokenizer.h"
#include "tokens_container.h"

int main() {
    Tokenizer tokenizer("1 + 2 / 3 - 122 * 0 * 2");

    do {
        tokenizer.next_token();
        std::cout << "TYPE " << get_token_type(tokenizer.last_tokens) << ": " << value_to_string(tokenizer.last_tokens) << std::endl;
    } while (tokenizer.last_tokens.val_type != value_type::null_t);
}
