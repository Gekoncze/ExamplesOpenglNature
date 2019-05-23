#pragma once
#include <exception>
#include <string>

namespace cz_mg_opengl
{
    class OpenglException : public std::exception
    {
    private:
        std::string message;

    public:
        OpenglException(std::string message);
        ~OpenglException();
        std::string getMessage();
    };
}
