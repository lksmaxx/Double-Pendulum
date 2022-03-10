#include "shader.hpp"

Shader::Shader(){}
Shader::~Shader(){}


void Shader::createProgram()
{
	GLCALL( m_id = glCreateProgram()	);
}

void Shader::attachVertShader(const std::string &path)
{
	//buffer file
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);	

	std::stringstream buffer;
	try
	{
		file.open(path);
		buffer << file.rdbuf();
		file.close();
	}
	catch(std::ifstream::failure e)
	{
		std::cerr << "ERROR::Could not open file: " << path << "\n" << e.what() << "\n";
		return;
	}

	//probaly there is a better way of doing this
	std::string t_str = buffer.str();
	const char *temp = t_str.c_str();

	uint32_t shader;

	GLCALL(	shader = glCreateShader(GL_VERTEX_SHADER)	);
	GLCALL(	glShaderSource(shader, 1, &temp,NULL)	);
	GLCALL(	glCompileShader(shader)	);
	checkErrors(shader,SHADER::VERTEX);

	GLCALL(	glAttachShader(m_id,shader)	);	
}

void Shader::attachFragShader(const std::string &path)
{
	//buffer file
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::stringstream buffer;
	try
	{
		file.open(path);
		buffer << file.rdbuf();
		file.close();
	}
	catch(std::ifstream::failure e)
	{
		std::cerr << "ERROR:: Could not open file: " << path << "\n" << e.what() <<"\n";
		return;
	}

	std::string t_str = buffer.str();
	const char *temp = t_str.c_str();

	uint32_t shader;

	GLCALL(	shader = glCreateShader(GL_FRAGMENT_SHADER)	);
	GLCALL(	glShaderSource(shader, 1, &temp,NULL)	);
	GLCALL(	glCompileShader(shader)	);
	checkErrors(shader,SHADER::FRAGMENT);

	GLCALL(	glAttachShader(m_id,shader)	);
}

void Shader::attachCompShader(const std::string &path)
{
	//buffer file
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::stringstream buffer;
	try
	{
		file.open(path);
		buffer << file.rdbuf();
		file.close();
	}
	catch(std::ifstream::failure e)
	{
		std::cerr << "ERROR:: Could not open file: " << path << "\n" << e.what() <<"\n";
		return;
	}

	std::string t_str = buffer.str();
	const char *temp = t_str.c_str();

	uint32_t shader;

	GLCALL(	shader = glCreateShader(GL_COMPUTE_SHADER)	);
	GLCALL(	glShaderSource(shader, 1, &temp,NULL)	);
	GLCALL(	glCompileShader(shader)	);
	checkErrors(shader,SHADER::COMPUTE);

	GLCALL(	glAttachShader(m_id,shader)	);
}




std::string SHADER::typeToString(SHADER::TYPE type)
{
	switch(type)
	{
		case SHADER::PROGRAM:
			return std::string("PROGRAM");
		case SHADER::VERTEX:
			return std::string("VERTEX");
		case SHADER::FRAGMENT:
			return std::string("FRAGMENT");
		case SHADER::COMPUTE:
			return std::string("COMPUTE");
		default:
			return std::string("UNDEFINED TYPE");
	}
}	



void Shader::checkErrors(uint32_t shader,SHADER::TYPE type)
{
	char buffer[1024];
	int result;
	

	if(type != SHADER::PROGRAM)
	{
		GLCALL(	glGetShaderiv(shader,GL_COMPILE_STATUS,&result)	);
		if(result == GL_FALSE)
		{
			GLCALL(	glGetShaderInfoLog(shader,1024,NULL,buffer)	);
			std::cout << "SHADER_" << SHADER::typeToString(type) << "_ERROR::" << buffer;
		}
		return;
	}
	GLCALL(	glGetProgramiv(shader,GL_LINK_STATUS,&result)	);
	if(result == GL_FALSE)
	{
		GLCALL(	glGetProgramInfoLog(shader,	1024,NULL,buffer)	);
		std::cout << "SHADER_PROGRAM_ERROR::" << buffer << "\n";
		return;
	}	
}

void Shader::linkProgram()
{
	GLCALL( glLinkProgram(m_id)	);
	checkErrors(m_id,SHADER::PROGRAM);
}

uint32_t Shader::getUniformLocation(const std::string &u_name)
{
	if(m_uniforms.find(u_name) == m_uniforms.end())
	{
		uint32_t l;
		GLCALL(	l = glGetUniformLocation(m_id,u_name.c_str())	);
		m_uniforms[u_name] = l;
		return l;
	}

	return m_uniforms[u_name];
}

void Shader::setUniform4f(const std::string &u_name,const std::vector<float> &values)
{
	if(values.size() > 3)
	{
		GLCALL(	glUniform4f(getUniformLocation(u_name),values[0], values[1], values[2], values[3])	);
	}
}

void Shader::setUniform1i(const std::string &u_name,int value)
{
	GLCALL(	glUniform1i(getUniformLocation(u_name), value)	);
}

void Shader::setUniform1f(const std::string &u_name,float value)
{
	GLCALL(	glUniform1f(getUniformLocation(u_name),value)	);
}

void Shader::setUniform4fv(const std::string &u_name,uint32_t count,const std::vector<float> &values)
{
	if(values.size() / 4 >= count)
	{
		GLCALL(	glUniform4fv(getUniformLocation(u_name),count,values.data())	);
	}
}
