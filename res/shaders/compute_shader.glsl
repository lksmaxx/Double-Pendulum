#version 430 core
layout(local_size_x = 1)in;

struct Pendulum
{
	float 		pad[4],
				a1,l1,a1s,m1,
				a2,l2,a2s,m2;
};

layout(std430,binding = 0) buffer PendBuf
{
	Pendulum pendulums[20];
};

layout(std430,binding = 1) buffer PointsBuf
{
	vec2	points[60];
};

#define p pendulums[my_id]
#define a1 pendulums[my_id].a1
#define a2 pendulums[my_id].a2
#define l1 pendulums[my_id].l1
#define l2 pendulums[my_id].l2
#define m1 pendulums[my_id].m1
#define m2 pendulums[my_id].m2
#define a1s pendulums[my_id].a1s
#define a2s pendulums[my_id].a2s

uniform float deltaTime;

void main()
{
 	const uint my_id = gl_GlobalInvocationID.x;
	
	float g = 1;
	float w1s = 0;
	float w2s = 0;
	//equations...
	float eq1_up1 = -g * ( 2 * m1 + m2 ) * sin(a1);
	float eq1_up2 = -m2 * g * sin( a1 - 2 * a2 );
	float eq1_up3 = -2 * sin( a1 - a2 ) * m2 * ( pow(a2s,2) * l2 + pow(a1s,2) * l1 * cos( a1 - a2 ));

	float eq1_dw1 = l1 * ( 2 * m1 + m2 - m2 * cos( 2 * a1 - 2 * a2 ) );

	w1s = ( eq1_up1 + eq1_up2 + eq1_up3 ) / eq1_dw1;

	float eq2_up1 = 2 * sin( a1 - a2 ) * ( pow(a1s,2) * l1 * ( m1 + m2 ) + g * ( m1 + m2 ) * cos(a1) + pow(a2s,2) * l2 * m2 * cos(a1 - a2));
	float eq2_dw1 = l2 * (2 * m1 + m2 - m2 * cos( 2 * a1 - 2 * a2 ));

	w2s = eq2_up1 / eq2_dw1;
	
	/*
	float num = (-g * (2 * m1 + m2) * sin(a1)) -
		(m2 * g * sin(a1 - 2 * a2)) -
		(2 * sin(a1 - a2) * m2 * (a2s*a2s * l2 + a1s * a1s * l1 * cos(a1 - a2)));
	float denom = l1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));

	w1s = num / denom;

	float num2 = (2 * sin(a1 - a2) * (a1s * a1s * l1 * (m1 + m2) + g * (m1 + m2) * cos(a1) + a2s * a2s * l2 * m2 * cos(a1 - a2)));
	float denom2 = l2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));

	w2s = num2 / denom2;
	*/

	a1s += w1s * deltaTime ;
	a2s += w2s * deltaTime;

	//a1s = 0.01;
	//a2s = -0.01;

	//a1 = 0;

	a1 += a1s * deltaTime;
	a2 += a2s * deltaTime;

	points[my_id * 3 + 0] = vec2(0);
	points[my_id * 3 + 1] = vec2(l1 * sin(a1), -l1 * cos(a1));
	points[my_id * 3 + 2] = vec2(l2 * sin(a2), -l2 * cos(a2)) + vec2(l1 * sin(a1), -l1 * cos(a1));
	
	//points[my_id * 3 + 0] = vec2(p.l1);
	//points[my_id * 3 + 1] = vec2(1);
	//points[my_id * 3 + 2] = vec2(3);
}
