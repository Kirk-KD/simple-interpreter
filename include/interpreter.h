#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast_visitor.h"
#include "parser.h"

class Interpreter : public AstVisitor {
public:
    VisitResult visit(const node_p& n);
};

#endif