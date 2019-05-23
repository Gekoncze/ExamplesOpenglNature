#pragma once
#include "VertexArrayHandle.h"
#include <string>
#include "FloatBuffer.h"

namespace cz_mg_opengl
{
    class VertexArray
    {
        NOCOPY(VertexArray)

    private:
        VertexArrayHandle vertexArray;

    public:
        VertexArray();
        ~VertexArray();

        VertexArrayHandle& getVertexArray()
        {
            return vertexArray;
        }

        void bind();
        void setAttribute(int location, FloatBuffer& buffer);
        void setAttributeInstance(int location, FloatBuffer& buffer, int divisor);
    };
}
