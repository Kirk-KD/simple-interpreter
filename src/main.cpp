#include <iostream>

#include "tokenizer.h"
#include "tokens_container.h"
#include "ast.h"

int main() {
    Tokenizer tokenizer("1 + 2 / 3 - 122 * 0 * 2");

    do {
        tokenizer.next_token();
        std::cout << "TYPE " << get_token_type(tokenizer.last_tokens) << ": " << value_to_string(tokenizer.last_tokens) << std::endl;
    } while (tokenizer.last_tokens.val_type != value_type::null_t);

    auto n = node_factory(
        node_type::bin_op,
        StaticTokensContainer(token<std::string>{token_type::plus, "+"}),
        node_factory(
            node_type::int_lit,
            StaticTokensContainer(token<int>{token_type::integer, 10}),
            null_node(),
            null_node()
        ),
        node_factory(
            node_type::int_lit,
            StaticTokensContainer(token<int>{token_type::integer, 20}),
            null_node(),
            null_node()
        )
    );
    std::cout << node_to_string(*n) << std::endl;
}
