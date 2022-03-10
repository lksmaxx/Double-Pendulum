#include "framebuffer.hpp"

FrameBuffer::FrameBuffer(){}
FrameBuffer::~FrameBuffer(){}

FrameBuffer::FrameBuffer(std::string name)
{
	m_name = name;

	GLCALL(	glGenFramebuffers(1,&m_id)	);
}

void FrameBuffer::bindTexture(uint32_t tex)
{
	GLCALL(	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,tex,0)	);
}
