#include "exception.h"

const char* Exception::what() {
    return message.c_str();
}

// User exceptions

UnexpectedCharacter::UnexpectedCharacter(char c, int pos) {
    message = fmt::format("Unexpected character: '{}' at position: {}", c, pos);
}

UnexpectedToken::UnexpectedToken(token_type got, token_type expected) {
    message = fmt::format("Unexpected token: Type {} (Type {} expected)", got, expected);
}

SyntaxError::SyntaxError(int pos, std::string detail) {
    message = fmt::format("Syntax error: {} at position: {}", detail, pos);
}

NameError::NameError(std::string name) {
    message = fmt::format("Name Error: '{}'", name);
}

NullValueError::NullValueError(std::string name) {
    message = fmt::format("Null Value Error: '{}' is null but is being accessed", name);
}

// Dev exceptions

IncompleteFeature::IncompleteFeature(std::string detail) {
    message = fmt::format("This feature is not yet implemented. Detail: {}", detail);
}

ShouldNotReach::ShouldNotReach(std::string detail) {
    message = fmt::format("This exception should not have been thrown! Detail: {}", detail);
}