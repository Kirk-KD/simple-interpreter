#include <iostream>

#include "tokenizer.h"
#include "tokens_container.h"

int main() {
    Tokenizer tokenizer("123 hi hello funny69_420_");
    TokensContainer container;

    do {
        container.val_type = tokenizer.next_token(container.token_i, container.token_f, container.token_s, container.token_c);
        std::cout << "TYPE " << container.val_type << ": " << container.val_to_string() << std::endl;
    } while (container.val_type != value_type::null_t);
}
