#pragma once
#include "Handle.h"

namespace cz_mg_opengl
{
    class VertexArrayHandle : public Handle
    {
	    NOCOPY(VertexArrayHandle)

    public:
	    VertexArrayHandle();
	    ~VertexArrayHandle();
    };
}
