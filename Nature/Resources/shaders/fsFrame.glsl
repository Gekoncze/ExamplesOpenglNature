#version 330
precision mediump float;
in vec2 frag_uv;
uniform sampler2D in_texture;
layout(location = 0) out vec4 color;

void main()
{
    color = texture(in_texture, frag_uv);
}