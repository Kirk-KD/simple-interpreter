#include "exception.h"

const char* Exception::what() {
    return message.c_str();
}

UnexpectedCharacter::UnexpectedCharacter(char c, int pos) {
    message = fmt::format("Unexpected character: '{}' at position: {}", c, pos);
}

UnexpectedToken::UnexpectedToken(token_type got, token_type expected) {
    message = fmt::format("Unexpected token: Type {} (Type {} expected)", got, expected);
}
