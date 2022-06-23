#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <fmt/core.h>

class Exception : public std::exception {
protected:
    std::string message;
public:
    const char* what();
};

class UnexpectedCharacter : public Exception {
public:
    UnexpectedCharacter(char c, int pos);
};

#endif