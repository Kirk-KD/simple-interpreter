#ifndef SYMTAB_H
#define SYMTAB_H

#include <map>
#include <string>
#include <memory>

#include "token.h"
#include "fmt/core.h"

enum symbol_type {
    builtin_type,
    var
};

struct symbol_value {
    bool is_null;
    value_type val_type;

    int value_i;
    float value_f;
    double value_d;
    std::string value_s;
};

symbol_value symbol_value_factory(int i);

symbol_value symbol_value_factory(float f);

symbol_value symbol_value_factory(double d);

symbol_value symbol_value_factory(std::string s);

symbol_value symbol_value_factory();

struct symbol {
    bool is_null;

    std::string name;
    symbol_type type;
    symbol_value value;
};

symbol builtin_type_symbol_factory(std::string name);

symbol var_symbol_factory(std::string name, symbol_value value);

struct symtab_value {
    bool is_null;
    value_type val_type;

    int value_i;
    float value_f;
    double value_d;
    std::string value_s;
};

class SymbolTable {
    std::map<std::string, symbol> symbols;
public:
    void set(std::string key, symbol sym);

    symbol get(std::string key);

    bool has(std::string key);

    std::string to_string();
};

#endif