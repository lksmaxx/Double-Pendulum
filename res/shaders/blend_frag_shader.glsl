#version 430 core

in vec2 f_texcoord;

out vec4 o_color;

uniform sampler2D t_points;

void main()
{
	vec2 tStep = vec2(1.0 / 1280.0, 1.0 / 720.0);
	vec4 tColor = 0.6 * texture(t_points,f_texcoord);
	
	
	tColor += 0.1 * texture(t_points,f_texcoord - vec2(tStep.x,0));
	tColor += 0.1 * texture(t_points,f_texcoord + vec2(tStep.x,0));
	tColor += 0.1 * texture(t_points,f_texcoord - vec2(0, tStep.y));
	tColor += 0.1 * texture(t_points,f_texcoord + vec2(0, tStep.y));

	o_color = 0.995 * tColor ;
}
