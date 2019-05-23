#version 330

layout(location = 0) in vec3 in_vertex;
uniform mat4 in_matrix;
uniform vec4 in_color;

out vec4 f_color;

void main()
{
    f_color = in_color;
    gl_Position = in_matrix * vec4(in_vertex, 1);
}