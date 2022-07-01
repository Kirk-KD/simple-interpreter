#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include "ast.h"
#include "exception.h"

class VisitResult {
public:
    value_type type;

    int value_i;
    float value_f;
    double value_d;
    std::string value_s;

    VisitResult(int v_i);

    VisitResult(float v_f);

    VisitResult(double v_d);

    VisitResult(std::string v_s);

    VisitResult();

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