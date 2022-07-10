#include "interpreter.h"

VisitResult Interpreter::visit(const node_p& n) {
    switch ((*n).type) {
        case node_type::int_lit:
            return VisitResult((*n).token_sc.token_i.value);
        case node_type::float_lit:
            return VisitResult((*n).token_sc.token_f.value);
        case node_type::double_lit:
            return VisitResult((*n).token_sc.token_d.value);
        case node_type::bin_op: {
            std::string op = (*n).token_sc.token_s.value;
            if (!(*n).left) {
                throw SyntaxError(-1, "missing left side of operator '" + op + "'"); // -1 is placeholder
            } else if (!(*n).right) {
                throw SyntaxError(-1, "missing right side of operator '" + op + "'");
            }
            if (op == "+") {
                return VisitResult(visit((*n).left) + visit((*n).right));
            } else if (op == "-") {
                return VisitResult(visit((*n).left) - visit((*n).right));
            } else if (op == "*") {
                return VisitResult(visit((*n).left) * visit((*n).right));
            } else if (op == "/") {
                return VisitResult(visit((*n).left) / visit((*n).right));
            }
        }
        case node_type::una_op: {
            std::string op = (*n).token_sc.token_s.value;
            if (op == "+") {
                VisitResult vr = visit((*n).right);
                if (vr.type == value_type::int_t) {
                    return VisitResult(vr.value_i);
                } else if (vr.type == value_type::float_t) {
                    return VisitResult(vr.value_f);
                }
            } else if (op == "-") {
                VisitResult vr = visit((*n).right);
                if (vr.type == value_type::int_t) {
                    return VisitResult(-vr.value_i);
                } else if (vr.type == value_type::float_t) {
                    return VisitResult(-vr.value_f);
                }
            }
        }
        case node_type::var_decl: {
            std::string key = (*(*n).var_node).token_sc.token_s.value;
            if ((*n).value_node) {
                VisitResult vr = visit((*n).value_node);
                switch (vr.type) {
                    case value_type::int_t:
                        symbols.set(key, var_symbol_factory(key, symbol_value_factory(vr.value_i)));
                        break;
                    case value_type::float_t:
                        symbols.set(key, var_symbol_factory(key, symbol_value_factory(vr.value_f)));
                        break;
                    case value_type::double_t:
                        symbols.set(key, var_symbol_factory(key, symbol_value_factory(vr.value_d)));
                        break;
                    default:
                        throw IncompleteFeature(fmt::format("var_decl of type {}", vr.type));
                }
            }
            return VisitResult();
        }
        case node_type::variable: {
            std::string key = (*n).token_sc.token_s.value;
            if (symbols.has(key)) {
                symbol s = symbols.get(key);
                if (s.type == symbol_type::var) {
                    switch (s.value.val_type) {
                        case value_type::int_t: return VisitResult(s.value.value_i); break;
                        case value_type::float_t: return VisitResult(s.value.value_f); break;
                        case value_type::double_t: return VisitResult(s.value.value_d); break;
                        case value_type::string_t: return VisitResult(s.value.value_s); break;
                        default: throw NullValueError(key);
                    }
                } else {
                    throw ShouldNotReach("symbol_type is not var in node_type::variable");
                }
            } else {
                throw NameError(key);
            }
        }
        case node_type::program:
            // temporary way of handling a program
            for (node_p &child : (*n).children) {
                VisitResult vr = visit(child);
                if (vr.type != value_type::null_t)
                    std::cout << vr.to_string() << std::endl;
            }
            std::cout << symbols.to_string() << std::endl;
            return VisitResult(0);
        default:
            throw IncompleteFeature(fmt::format("Unknown node type {} in Interpreter::visit", (*n).type));
    }
}
