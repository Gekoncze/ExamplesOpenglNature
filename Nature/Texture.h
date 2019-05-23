#pragma once
#include "TextureHandle.h"
#include <vector>

namespace cz_mg_opengl
{
    class Texture
    {
        NOCOPY(Texture)

    private:
        TextureHandle texture;

    public:
        Texture(int width, int height, int min_filter, int mag_filter);
        Texture(int width, int height, std::vector<GLubyte>& data, bool mipmap);
        ~Texture();
        TextureHandle& getTexture();
    };
}
