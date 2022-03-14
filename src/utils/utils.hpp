#pragma once 

#include <iostream>
#include <vector>


struct Pendulum
{
	float 		pad[4],			//padding for glsl std140 and zero position for vertex data
				a1,l1,a1s,m1,
				a2,l2,als,m2;
};

///interpolate between two vec4 with @ratio as weight, where if ratio is 1 dest will be equal to v2
void mix_vec4(const std::vector<float> &v1,const std::vector<float> &v2,float ratio, std::vector<float> &dest);
