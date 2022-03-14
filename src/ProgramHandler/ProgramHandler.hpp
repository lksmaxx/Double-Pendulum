#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include <gl_utils/gl_utils.hpp>
#include <utils/utils.hpp>
#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <framebuffer/framebuffer.hpp>


static bool reset = false;

//test commentary

class ProgramHandler
{
	public:
	ProgramHandler();
	~ProgramHandler();

	std::string s_test;

	///Program main loop
	void run();

	private:
	GLFWwindow 		*m_window;
	bool 			m_reset;

	const uint32_t 	m_max_pendulums = 500;
	uint32_t 		m_num_pendulums = 500;
	FrameBuffer 	m_framebuffer;
	GL::Context 	m_lines_context,m_points_context;
	GL::Quad 		m_quad_screen;
	Texture 		m_lines_texture,m_points_texture;
	Shader 			m_lines_shader,m_points_shader,m_screen_shader,m_compute_shader,m_blend_shader;

	std::vector<Pendulum> m_pendulums;
	std::vector<float> m_pColors;

	void createPendulums();
	void resetPendulums();


};
