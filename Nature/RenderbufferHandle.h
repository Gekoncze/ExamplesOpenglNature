#pragma once
#include "Handle.h"

namespace cz_mg_opengl
{
    class RenderbufferHandle : public Handle
    {
	    NOCOPY(RenderbufferHandle)

    public:
	    RenderbufferHandle();
	    ~RenderbufferHandle();
    };
}
