#version 430 core

layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_texcoord;

out vec2 f_texcoord;

void main()
{
	gl_Position = vec4(v_pos,0,1);
	f_texcoord = v_texcoord;
}
