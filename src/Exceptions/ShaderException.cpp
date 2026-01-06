#include "ShaderException.h"

ShaderException::ShaderException(const char *message) {
    this->message = message;
}

const char * ShaderException::what() const noexcept {
    return this->message.c_str();
}