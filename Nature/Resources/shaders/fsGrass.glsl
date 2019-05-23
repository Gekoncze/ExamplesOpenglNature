#version 330
precision mediump float;
in vec2 frag_uv;
in vec3 frag_color;
uniform sampler2D in_texture;
layout(location = 0) out vec4 color;

void main()
{
    vec4 tex_color = texture(in_texture, frag_uv);
    if(tex_color.a < 0.5) discard;
    tex_color.a = 1.0;
    color = tex_color * vec4(frag_color, 1);
}