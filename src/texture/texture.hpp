#pragma once 
#include <iostream>
#include <gl_utils/gl_utils.hpp>


class Texture
{
	public:
	Texture();
	~Texture();

	Texture(uint32_t width,uint32_t height,const void *data = NULL);
	
	inline void setSlot(uint32_t slot){GLCALL(	glActiveTexture(GL_TEXTURE0 + slot)	); m_slot = slot;};
	inline void bind(){GLCALL( glBindTexture(GL_TEXTURE_2D,m_id)	);};
	inline void bind(uint32_t slot){setSlot(slot); bind();};
	inline void unBind(){GLCALL(	glActiveTexture(GL_TEXTURE0)	);};

	inline uint32_t getId()	{return m_id;};
	private:
	uint32_t m_id,m_slot,m_width,m_height;
};
