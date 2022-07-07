#include "ast.h"

/**
 * Makes a nullptr unique_ptr of type `node`.
 */
node_p null_node() {
    return node_p{};
}

/**
 * A factory for constructing a `node` struct.
 * 
 * @param type node type
 * @param token_sc a static tokne container
 * @param left left child node
 * @param right right child node
 * @return an unique pointer to the `node` constructed.
 */
node_p node_factory(
    node_type type,
    StaticTokensContainer token_sc,
    node_p left,
    node_p right
) {
    auto node_ptr = std::make_unique<node>();
    (*node_ptr).type = type;
    (*node_ptr).token_sc = token_sc;
    (*node_ptr).left = left ? std::move(left) : null_node();
    (*node_ptr).right = right ? std::move(right) : null_node();
    return node_ptr;
}

/**
 * A variant of node_factory for the var_decl node.
 * 
 * @param var_node variable node
 * @param type_node type_spec node
 * @param value_node the value, could be any type retured by expr()
 * @return an unique pointer to the `node` constructed.
 */
node_p var_decl_factory(
    std::unique_ptr<node> var_node,
    std::unique_ptr<node> type_node,
    std::unique_ptr<node> value_node
) {
    auto node_ptr = std::make_unique<node>();
    (*node_ptr).type = node_type::var_decl;
    (*node_ptr).var_node = std::move(var_node);
    (*node_ptr).type_node = std::move(type_node);
    (*node_ptr).value_node = std::move(value_node);
    return node_ptr;
}

/**
 * A variant of node_factory for nodes with children nodes only, with no other features.
 * 
 * @param children vector of children nodes
 * @return an unique pointer to the `node` constructed.
 */
node_p stmt_list_factory(node_type type, std::vector<node_p> children) {
    auto node_ptr = std::make_unique<node>();
    (*node_ptr).type = type;
    (*node_ptr).children = std::move(children);
    return node_ptr;
}

/**
 * Makes a node that holds a type of `error_node`.
 */
node_p err_node() {
    return node_factory(node_type::error_node);
}

/**
 * Recursively converts a `node` to string, for logging purposes.
 * 
 * @param n The node to be converted.
 * @return Converted result.
 */
std::string node_to_string(const node& n) {
    std::string r = "Node(Type=" + std::to_string(n.type) +
                    ", CTC=CTC(Type=" + std::to_string(get_token_type(n.token_sc)) +
                    ", Value=" + value_to_string(n.token_sc) +
                    "), Left=" + (n.left ? node_to_string(*n.left) : "NULL") +
                    ", Right=" + (n.right ? node_to_string(*n.right) : "NULL") +
                    ", Children=[";
    
    bool first = true;
    for (const auto& c : n.children) {
        if (first) first = false;
        else r += ", ";
        r += node_to_string(*c);
    }

    r += "])";

    return r;
}
