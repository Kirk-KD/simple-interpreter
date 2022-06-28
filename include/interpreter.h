#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>

#include "ast_visitor.h"
#include "parser.h"
#include "exception.h"

class Interpreter : public AstVisitor {
public:
    VisitResult visit(const node_p& n);
};

#endif