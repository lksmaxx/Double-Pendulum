#pragma once 

#include <iostream>


struct Pendulum
{
	float 		pad[4],			//padding for glsl std140 and zero position for vertex data
				a1,l1,a1s,m1,
				a2,l2,als,m2;
};
