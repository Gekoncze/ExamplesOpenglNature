#pragma once
#include "Handle.h"

namespace cz_mg_opengl
{
    class TextureHandle : public Handle
    {
	    NOCOPY(TextureHandle)

    public:
	    TextureHandle();
	    ~TextureHandle();
    };
}
