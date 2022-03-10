#version 430 core

in vec2 f_texcoord;

out vec4 o_color;

uniform sampler2D t_points;

void main()
{
	o_color = 0.999 * texture(t_points,f_texcoord);
}
