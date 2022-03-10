#version 430 core

in vec2 f_texcoord;

uniform sampler2D t_lines;
uniform sampler2D t_points;

out vec4 out_color;

void main()
{
	out_color =max( texture(t_lines,f_texcoord),texture(t_points,f_texcoord));
}
