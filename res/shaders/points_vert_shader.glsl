#version 430 core

layout(location = 0) in vec2 v_pos;

flat out int f_id;

void main()
{
	gl_Position = vec4(v_pos + vec2(0,1),0,1); 
	f_id = gl_VertexID;
}
