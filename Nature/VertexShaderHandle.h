#pragma once
#include "Handle.h"

namespace cz_mg_opengl
{
    class VertexShaderHandle : public Handle
    {
	    NOCOPY(VertexShaderHandle)

    public:
	    VertexShaderHandle();
	    ~VertexShaderHandle();
    };
}
