#include "ast_visitor.h"

VisitResult::VisitResult(int v_i) {
    value_i = v_i;
    type = value_type::int_t;
}

VisitResult::VisitResult(float v_f) {
    value_f = v_f;
    type = value_type::float_t;
}

VisitResult::VisitResult(double v_d) {
    value_d = v_d;
    type = value_type::double_t;
}

VisitResult::VisitResult(std::string v_s) {
    value_s = v_s;
    type = value_type::string_t;
}

VisitResult::~VisitResult() {}

std::string VisitResult::to_string() {
    switch (type) {
        case value_type::int_t:
            return std::to_string(value_i);
        case value_type::float_t:
            return std::to_string(value_f);
        case value_type::double_t:
            return std::to_string(value_d);
        case value_type::string_t:
            return value_s;
        case value_type::null_t:
            return "NULL";
        default:
            return "Unexpected to_string type";
    }
}

VisitResult VisitResult::operator+(const VisitResult& right) {
    if (type == value_type::float_t && right.type == value_type::int_t) {
        return VisitResult(value_f + right.value_i);
    } else if (type == value_type::int_t && right.type == value_type::float_t) {
        return VisitResult(value_i + right.value_f);
    } else if (type == value_type::float_t && right.type == value_type::float_t) {
        return VisitResult(value_f + right.value_f);
    } else if (type == value_type::int_t && right.type == value_type::int_t) {
        return VisitResult(value_i + right.value_i);
    } else if (type == value_type::string_t && right.type == value_type::string_t) {
        return VisitResult(value_s + right.value_s);
    } else {
        // TODO error handling
    }
}

VisitResult VisitResult::operator-(const VisitResult& right) {
    if (type == value_type::float_t && right.type == value_type::int_t) {
        return VisitResult(value_f - right.value_i);
    } else if (type == value_type::int_t && right.type == value_type::float_t) {
        return VisitResult(value_i - right.value_f);
    } else if (type == value_type::float_t && right.type == value_type::float_t) {
        return VisitResult(value_f - right.value_f);
    } else if (type == value_type::int_t && right.type == value_type::int_t) {
        return VisitResult(value_i - right.value_i);
    } else {
        // TODO error handling
    }
}

VisitResult VisitResult::operator*(const VisitResult& right) {
    if (type == value_type::float_t && right.type == value_type::int_t) {
        return VisitResult(value_f * right.value_i);
    } else if (type == value_type::int_t && right.type == value_type::float_t) {
        return VisitResult(value_i * right.value_f);
    } else if (type == value_type::float_t && right.type == value_type::float_t) {
        return VisitResult(value_f * right.value_f);
    } else if (type == value_type::int_t && right.type == value_type::int_t) {
        return VisitResult(value_i * right.value_i);
    } else {
        // TODO error handling
    }
}

VisitResult VisitResult::operator/(const VisitResult& right) {
    if (type == value_type::float_t && right.type == value_type::int_t) {
        return VisitResult(value_f / right.value_i);
    } else if (type == value_type::int_t && right.type == value_type::float_t) {
        return VisitResult(value_i / right.value_f);
    } else if (type == value_type::float_t && right.type == value_type::float_t) {
        return VisitResult(value_f / right.value_f);
    } else if (type == value_type::int_t && right.type == value_type::int_t) {
        return VisitResult(value_i / right.value_i);
    } else {
        // TODO error handling
    }
}
