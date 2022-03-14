#version 430 core

layout(location = 0) in vec2 v_pos;

uniform vec4 u_colors[500];

out vec4 f_color;

void main()
{
	float ratio = 1280.0f / 720.0f;
	vec2 tPos = vec2(v_pos.x / ratio, v_pos.y + 1);
	gl_Position = vec4(tPos,0,1);
	f_color = u_colors[int(floor(gl_VertexID / 3.0))];
}
