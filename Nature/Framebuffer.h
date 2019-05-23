#pragma once
#include "FramebufferHandle.h"
#include "RenderbufferHandle.h"
#include "Texture.h"
#include "OpenglException.h"

namespace cz_mg_opengl
{
    class Framebuffer
    {
        NOCOPY(Framebuffer)

    private:
        FramebufferHandle framebuffer;
        RenderbufferHandle renderbuffer;
        Texture texture;
        int width, height;
        GLint oldFramebuffer;

    public:
        Framebuffer(int width, int height);
        ~Framebuffer();

        Texture& getTexture();
        void use();
        void unuse();
    };
}
