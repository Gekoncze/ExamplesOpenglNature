#pragma once
#include <GL/glew.h>
#include <string>
#include "Nocopy.h"

namespace cz_mg_opengl
{
    class Opengl
    {
    public:
        static void checkError(std::string message);
        static std::string errorToString(GLenum error);
        static std::string frameBufferErrorToString(GLenum error);
    };
}
