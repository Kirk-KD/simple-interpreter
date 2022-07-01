#include "symtab.h"

void SymbolTable::set(std::string key, symtab_value val) {
    symbols[key] = val;
}

void SymbolTable::set(std::string key) {
    symbols[key] = symtab_value{true, value_type::null_t};
}

symtab_value SymbolTable::get(std::string key) {
    if (has(key)) return symbols[key];
    else return symtab_value{true};
}

bool SymbolTable::has(std::string key) {
    return symbols.find(key) != symbols.end();
}

std::string SymbolTable::to_string() {
    std::string s = "Symtab Content\n--------------\n";
    for (auto const& [key, val] : symbols) {
        std::string val_string;
        switch (val.val_type) {
            case value_type::int_t: val_string = std::to_string(val.value_i); break;
            case value_type::float_t: val_string = std::to_string(val.value_f); break;
            case value_type::double_t: val_string = std::to_string(val.value_d); break;
            case value_type::string_t: val_string = val.value_s; break;
            case value_type::null_t: val_string = "NULL"; break;
        }
        s += fmt::format("{} : {} (value type {})\n", key, val_string, val.val_type);
    }
    s += "--------------";

    return s;
}
