#version 330
precision mediump float;
in vec2 frag_uv;
uniform sampler2D in_texture;
uniform sampler2D in_texture_2;
layout(location = 0) out vec4 color;

void main()
{
    vec4 t1 = texture(in_texture, frag_uv);
    vec4 t2 = texture(in_texture_2, frag_uv);
    //color = t1 + vec4(t2.x / 4.0f, t2.y / 4.0f, t2.z / 4.0f, 0);
	float blurIntensity = 0.2;
	color = t1*(1.0 - blurIntensity) + t2*blurIntensity;
}