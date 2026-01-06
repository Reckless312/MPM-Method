#include "ProgramException.h"

ProgramException::ProgramException(const char *message) {
    this->message = message;
}

const char * ProgramException::what() const noexcept {
    return this->message.c_str();
}