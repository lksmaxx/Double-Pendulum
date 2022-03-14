#version 430 core

layout(location = 0) in vec2 v_pos;

uniform vec4 u_colors[20];

out vec4 f_color;

void main()
{
	gl_Position = vec4(v_pos + vec2(0,1),0,1);
	f_color = u_colors[int(floor(gl_VertexID / 3.0))];
}
