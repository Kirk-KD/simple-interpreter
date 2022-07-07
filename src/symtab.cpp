#include "symtab.h"

symbol_value symbol_value_factory(int i) {
    return symbol_value{false, value_type::int_t, i, 0, 0, ""};
}

symbol_value symbol_value_factory(float f) {
    return symbol_value{false, value_type::float_t, 0, f, 0, ""};
}

symbol_value symbol_value_factory(double d) {
    return symbol_value{false, value_type::double_t, 0, 0, d, ""};
}

symbol_value symbol_value_factory(std::string s) {
    return symbol_value{false, value_type::string_t, 0, 0, 0, s};
}

symbol_value symbol_value_factory() {
    return symbol_value{true};
}

symbol builtin_type_symbol_factory(std::string name) {
    return symbol{false, name, symbol_type::builtin_type, symbol_value{true}};
}

symbol var_symbol_factory(std::string name, symbol_value value) {
    return symbol{false, name, symbol_type::var, value};
}

void SymbolTable::set(std::string key, symbol sym) {
    symbols[key] = sym;
}

symbol SymbolTable::get(std::string key) {
    if (has(key)) return symbols[key];
    else return symbol{true};
}

bool SymbolTable::has(std::string key) {
    return symbols.find(key) != symbols.end();
}

std::string SymbolTable::to_string() {
    std::string s = "Symtab Content\n--------------\n";

    for (auto const& [key, sym] : symbols) {
        std::string res;
        switch (sym.type) {
            case symbol_type::builtin_type:
                res = fmt::format("{} : BuiltinType(name={})", key, sym.name);
                break;
            case symbol_type::var: {
                std::string val;

                switch (sym.value.val_type) {
                    case value_type::int_t: val = std::to_string(sym.value.value_i); break;
                    case value_type::float_t: val = std::to_string(sym.value.value_f); break;
                    case value_type::double_t: val = std::to_string(sym.value.value_d) + "d"; break;
                    case value_type::string_t: val = "\"" + sym.value.value_s + "\""; break;
                    case value_type::null_t: val = ""; break;
                }

                res = fmt::format("{} : Var(name={}, value={})", key, sym.name, val);
                break;
            }
        }

        s += res + "\n";
    }

    // for (auto const& [key, val] : symbols) {
    //     std::string val_string;
    //     switch (val.val_type) {
    //         case value_type::int_t: val_string = std::to_string(val.value_i); break;
    //         case value_type::float_t: val_string = std::to_string(val.value_f); break;
    //         case value_type::double_t: val_string = std::to_string(val.value_d); break;
    //         case value_type::string_t: val_string = val.value_s; break;
    //         case value_type::null_t: val_string = "NULL"; break;
    //     }
    //     s += fmt::format("{} : {} (value type {})\n", key, val_string, val.val_type);
    // }
    // s += "--------------";

    return s + "--------------";
}
