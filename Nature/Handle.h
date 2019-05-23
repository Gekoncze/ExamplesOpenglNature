#pragma once
#include "Opengl.h"

namespace cz_mg_opengl
{
    class Handle
    {
	    NOCOPY(Handle)

    protected:
	    GLuint handle;

    public:
	    Handle();
	    virtual ~Handle();

	    GLuint getHandle()
	    {
		    return handle;
	    }
    };
}
