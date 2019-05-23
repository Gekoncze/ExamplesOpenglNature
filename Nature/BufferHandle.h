#pragma once
#include "Handle.h"

namespace cz_mg_opengl
{
    class BufferHandle : public Handle
    {
        NOCOPY(BufferHandle)

    public:
        BufferHandle();
        ~BufferHandle();
    };
}
