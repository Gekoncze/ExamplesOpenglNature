#pragma once
#include "BufferHandle.h"

namespace cz_mg_opengl
{
    class FloatBuffer
    {
        NOCOPY(FloatBuffer)

    private:
        int n = 0;
        int count = 0;
        BufferHandle buffer;

    public:
        FloatBuffer(float* data, int n, int count);
        FloatBuffer();
        ~FloatBuffer();

        BufferHandle& getBuffer();
        int getN();
        void setDataStatic(float* data, int n, int count);
        void setDataStream(float* data, int n, int count);

    private:
        void setData(float* data, int n, int count, int usage);
    };
}
