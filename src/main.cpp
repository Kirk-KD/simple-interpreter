#include <iostream>

#include "tokenizer.h"
#include "tokens_container.h"

int main() {
    Tokenizer tokenizer("1 + 2 / 3 - 122 * 0 * 2");

    do {
        tokenizer.next_token();
        std::cout << "TYPE " << tokenizer.last_tokens.get_token_type() << ": " << tokenizer.last_tokens.to_string() << std::endl;
    } while (tokenizer.last_tokens.val_type != value_type::null_t);
}
