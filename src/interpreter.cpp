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
            return VisitResult("var_decl placeholder");
        }
        case node_type::program:
            for (node_p &child : (*n).children) {
                // temporary way of handling a program - outputing the calculated value of each line
                VisitResult vr = visit(child);
                std::cout << vr.to_string() << std::endl;
            }
            return VisitResult(0);
        default:
            throw IncompleteFeature(fmt::format("Unknown node type {} in Interpreter::visit", (*n).type));
    }
}
