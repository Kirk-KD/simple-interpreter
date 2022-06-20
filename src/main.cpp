#include <iostream>

#include "tokenizer.h"
#include "tokens_container.h"

int main() {
    Tokenizer tokenizer("123 hi omg _this__w0rks _________ nice69_420");

    do {
        tokenizer.next_token();
        std::cout << "TYPE " << tokenizer.last_tokens.val_type << ": " << tokenizer.last_tokens.to_string() << std::endl;
    } while (tokenizer.last_tokens.val_type != value_type::null_t);
}
