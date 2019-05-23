#pragma once
#include "Handle.h"

namespace cz_mg_opengl
{
    class FramebufferHandle : public Handle
    {
	    NOCOPY(FramebufferHandle)
    public:
	    FramebufferHandle();
	    ~FramebufferHandle();
    };
}
