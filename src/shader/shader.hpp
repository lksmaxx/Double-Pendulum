#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <gl_utils/gl_utils.hpp>
#include <vector>
#include <map>

namespace SHADER
{
	enum TYPE{PROGRAM, VERTEX,FRAGMENT,COMPUTE};
	std::string typeToString(SHADER::TYPE type);
	
};

class Shader
{
	public:
	Shader();

	void createProgram();
	void attachVertShader(const std::string &path);
	void attachFragShader(const std::string &path);
	void attachCompShader(const std::string &path);

	void linkProgram();

	inline void use(){GLCALL(	glUseProgram(m_id)	);};

	void setUniform4f(const std::string &u_name,const std::vector<float> &values);
	void setUniform1i(const std::string &u_name,int value);
	void setUniform1f(const std::string &u_name,float value);
	void setUniform4fv(const std::string &u_name,uint32_t count,const std::vector<float> &values);

	~Shader();

	private:
	uint32_t m_id;
	std::map<std::string,uint32_t> m_uniforms;

	void checkErrors(uint32_t shader,SHADER::TYPE type);
	uint32_t getUniformLocation(const std::string &u_name);
};
