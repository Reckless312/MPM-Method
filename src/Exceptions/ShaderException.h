#ifndef MPM_METHOD_SHADEREXCEPTION_H
#define MPM_METHOD_SHADEREXCEPTION_H
#include <string>

class ShaderException: public std::exception {
public:
    explicit ShaderException(const char* message);
    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string message;
};

#endif