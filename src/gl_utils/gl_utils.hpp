#pragma once

#include <iostream>
#include <glad/glad.h>

#ifdef DEBUG
#define GLCALL(x) \
{\
	glClearErrors();\
	x;\
	if(glCheckErrors())\
		std::cout << "GLCALL:" << #x << "	FILE:" << __FILE__ << "	LINE:" << __LINE__ <<"\n";\
}
#else
#define GLCALL(x) x
#endif

bool glCheckErrors();
void glClearErrors();


namespace GL
{
	struct Context
	{
		uint32_t vao,vbo,ebo,ssbo;
	};

	class Quad
	{
		public:
		Quad();
		void init();

		inline uint32_t getVao(){return m_vao;};
		inline uint32_t getVbo(){return m_vbo;};
		inline uint32_t getEbo(){return m_ebo;};
		inline void bindVao()	{glBindVertexArray(m_vao);};
		inline void bindVbo()	{glBindBuffer(GL_ARRAY_BUFFER,m_vbo);};
		inline void bindEbo()	{glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo);};
		inline void bindAll()	{bindVao(); bindVbo(); bindEbo();};

		~Quad();
		
		private:
		uint32_t m_vao,m_vbo,m_ebo;
	};
};
