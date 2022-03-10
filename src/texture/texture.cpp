#include "texture.hpp"

Texture::Texture(){}
Texture::~Texture(){}

Texture::Texture(uint32_t width,uint32_t height,const void *data) : m_width(width),m_height(height)
{
	GLCALL(	glGenTextures(1,&this->m_id)	);

	bind();
	
	GLCALL(	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)	);	
	GLCALL(	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)	);
	GLCALL(	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)	);
	GLCALL(	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)	);	

	GLCALL( glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F, width, height,	0,GL_RGBA,GL_FLOAT,data)	);
}
