#pragma once

#include <iostream>
#include <gl_utils/gl_utils.hpp>
#include <texture/texture.hpp>


class FrameBuffer
{
	public:
	FrameBuffer();
	~FrameBuffer();

	FrameBuffer(std::string name);

	inline void bind() const{GLCALL(	glBindFramebuffer(GL_FRAMEBUFFER,m_id)	);};
	inline void unBind()const{GLCALL(	glBindFramebuffer(GL_FRAMEBUFFER,0)	);};

	void bindTexture(uint32_t tex);
	private:
	uint32_t m_id;
	std::string m_name;
};
