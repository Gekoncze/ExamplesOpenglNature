#pragma once
#include "Handle.h"

namespace cz_mg_opengl
{
    class FragmentShaderHandle : public Handle
    {
	    NOCOPY(FragmentShaderHandle)

    public:
	    FragmentShaderHandle();
	    ~FragmentShaderHandle();
    };
}
