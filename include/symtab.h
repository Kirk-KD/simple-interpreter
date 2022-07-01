#ifndef SYMTAB_H
#define SYMTAB_H

#include <map>
#include <string>

#include "token.h"
#include "fmt/core.h"

struct symtab_value {
    bool is_null;

    value_type val_type;

    int value_i;
    float value_f;
    double value_d;
    std::string value_s;
};

class SymbolTable {
    std::map<std::string, symtab_value> symbols;
public:
    void set(std::string key, symtab_value val);

    void set(std::string key);

    symtab_value get(std::string key);

    bool has(std::string key);

    std::string to_string();
};

#endif