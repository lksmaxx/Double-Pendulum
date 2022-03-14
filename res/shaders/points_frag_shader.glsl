#version 430

uniform vec4 u_colors[500];

flat in int f_id;

out vec4 o_color;

void main()
{
	o_color = u_colors[f_id];
}
