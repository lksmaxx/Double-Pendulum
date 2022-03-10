#include "gl_utils.hpp"

void glClearErrors()
{
	while( glGetError() != GL_NO_ERROR)
	{
		//do nothing
	}
}

bool glCheckErrors()
{
	GLenum error = glGetError();


	bool result = false;
	while(error != GL_NO_ERROR)
	{
		std::string error_type;
		switch(error)
		{	
			case GL_INVALID_ENUM:
				error_type += "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error_type += "GL_INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				error_type += "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error_type += "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			case GL_OUT_OF_MEMORY:
				error_type += "GL_OUT_OF_MEMORY";
				break;
			case GL_STACK_UNDERFLOW:
				error_type += "GL_STACK_UNDERFLOW";
				break;
			case GL_STACK_OVERFLOW:
				error_type += "GL_STACK_OVERFLOW";
				break;
			default:
				error_type += "UNDEFINED";
				break;
		}
		result = true;
		error = glGetError();

		std::cout << "GL_ERROR::" << error_type << "\n";
	}
	return result;
}

using namespace GL;

Quad::Quad(){}
Quad::~Quad(){}

void Quad::init()
{
	glGenVertexArrays(1,&m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1,&m_vbo);
	glGenBuffers(1,&m_ebo);

	glBindBuffer(GL_ARRAY_BUFFER,m_vbo);

	float vertices[]=
	{
		-1.0, 1.0,
		 1.0, 1.0,
		 1.0,-1.0,
		-1.0,-1.0
	};

	float texcoord[]=
	{
		0.0,1.0,
		1.0,1.0,
		1.0,0.0,
		0.0,0.0
	};

	uint32_t indices[]=
	{
		0,1,2,
		0,2,3
	};

	GLCALL(	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices) + sizeof(texcoord),vertices,GL_STATIC_DRAW)	);
	GLCALL( glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertices),sizeof(texcoord),texcoord)	);

	GLCALL( glEnableVertexAttribArray(0)	);
	GLCALL(	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(const void*)0)	);
	GLCALL(	glEnableVertexAttribArray(1)	);
	GLCALL(	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(const void*) sizeof(vertices))	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}









