#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include "ast.h"

class VisitResult {
public:
    value_type type;

    int value_i;
    float value_f;
    std::string value_s;

    VisitResult(int v_i);

    VisitResult(float v_f);

    VisitResult(std::string v_s);

    ~VisitResult();

    std::string to_string();

    VisitResult operator+ (const VisitResult& left);

    VisitResult operator- (const VisitResult& left);

    VisitResult operator* (const VisitResult& left);

    VisitResult operator/ (const VisitResult& left);
};

class AstVisitor {
protected:
    virtual VisitResult visit(const node_p&) = 0;
};

#endif