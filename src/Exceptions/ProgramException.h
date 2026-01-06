#ifndef MPM_METHOD_PROGRAMEXCEPTION_H
#define MPM_METHOD_PROGRAMEXCEPTION_H
#include <exception>
#include <string>

class ProgramException: public std::exception {
private:
    std::string message;
public:
    explicit ProgramException(const char* message);
    [[nodiscard]] const char* what() const noexcept override;
};

#endif