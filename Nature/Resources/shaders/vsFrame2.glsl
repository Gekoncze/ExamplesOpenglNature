#version 330

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_uv;
uniform mat4 in_matrix;

out vec2 frag_uv;

void main()
{
    frag_uv = in_uv;
    gl_Position = in_matrix * vec4(in_vertex, 1);
}