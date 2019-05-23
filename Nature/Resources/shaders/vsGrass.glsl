#version 330

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_color;
layout(location = 3) in vec3 in_pos;
layout(location = 4) in float in_pliability;

uniform mat4 in_matrix_rotation;
uniform mat4 in_matrix;
uniform float in_wind_x;
uniform float in_wind_y;

out vec2 frag_uv;
out vec3 frag_color;

void main()
{
    frag_uv = in_uv;
	frag_color = in_color;

    vec4 p = ((in_matrix_rotation * vec4(in_vertex, 1.0)) + vec4(in_pos*2, 1.0));
    if(gl_VertexID == 1 || gl_VertexID == 2 || gl_VertexID == 3) p.x += in_pliability * in_wind_x;
    if(gl_VertexID == 1 || gl_VertexID == 2 || gl_VertexID == 3) p.y += in_pliability * in_wind_y;
    gl_Position = in_matrix * p;
}