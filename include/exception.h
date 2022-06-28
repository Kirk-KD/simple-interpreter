#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <fmt/core.h>

#include "tokens_container.h"

class Exception : public std::exception {
protected:
    std::string message;
public:
    const char* what();
};

// User exceptions

class UnexpectedCharacter : public Exception {
public:
    UnexpectedCharacter(char c, int pos);
};

class UnexpectedToken : public Exception {
public:
    UnexpectedToken(token_type got, token_type expected);
};

class SyntaxError : public Exception {
public:
    SyntaxError(int pos, std::string detail);
};

// Dev exceptions

class IncompleteFeature : public Exception {
public:
    IncompleteFeature();
};

class ShouldNotReach : public Exception {
public:
    ShouldNotReach(std::string detail);
};

#endif