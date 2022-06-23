#include "exception.h"

const char* Exception::what() {
    return message.c_str();
}

UnexpectedCharacter::UnexpectedCharacter(char c, int pos) {
    message = fmt::format("Unexpected character: '{}' at position: {}", c, pos);
}
