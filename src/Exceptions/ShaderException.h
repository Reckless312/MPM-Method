#ifndef MPM_METHOD_SHADEREXCEPTION_H
#define MPM_METHOD_SHADEREXCEPTION_H
#include <string>

class ShaderException: public std::exception {
private:
    std::string message;
public:
    explicit ShaderException(const char* message);
    [[nodiscard]] const char* what() const noexcept override;
};

#endif