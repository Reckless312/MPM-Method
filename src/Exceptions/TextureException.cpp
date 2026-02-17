#include "TextureException.h"

TextureException::TextureException(const char *message) {
    this->message = message;
}

const char * TextureException::what() const noexcept {
    return this->message.c_str();
}
