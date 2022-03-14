#include "utils.hpp"

void mix_vec4(const std::vector<float> &v1,const std::vector<float> &v2,float ratio,std::vector<float> &dest)
{
	if(v1.size() < 4 || v2.size() < 4) return;

	if(dest.size() < 4)
	{
		dest.resize(4);
	}
	
	if(ratio > 1) ratio = 1;

	for(int i = 0; i < 4; i++)
	{
		dest[i] = ratio * v2[i] + (1 - ratio) * v1[i]; 
	}
}
