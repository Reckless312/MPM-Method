#ifndef MPM_METHOD_TEXTUREEXCEPTION_H
#define MPM_METHOD_TEXTUREEXCEPTION_H
#include <exception>
#include <string>


class TextureException: public std::exception {
public:
    explicit TextureException(const char* message);
    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string message;
};


#endif