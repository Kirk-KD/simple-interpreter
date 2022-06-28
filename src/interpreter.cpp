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
        default:
            throw IncompleteFeature();
    }
}
