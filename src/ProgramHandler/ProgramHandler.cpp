#include "ProgramHandler.hpp"

void ProgramHandler::createPendulums()
{
	m_pendulums.resize(m_max_pendulums);

	m_pColors = std::vector<float>(
			{
				1.0,1.0,1.0,1.0,
				1.0,0.0,0.0,1.0,
				1.0,1.0,0.0,1.0,
				0.0,1.0,0.0,1.0,
				0.0,1.0,1.0,1.0,
				1.0,0.0,1.0,1.0,
				0.0,0.0,1.0,1.0
			});
}

void ProgramHandler::resetPendulums()
{
	float i = 0;
	for(Pendulum &p : m_pendulums)
	{
		p = {0};

		p.a1 = (M_PI / 2) + i/ 100000;
		p.a2 = 3 * M_PI / 4;
		p.l1 = 0.5;
		p.l2 = 0.5;

		p.m1 = 40;
		p.m2 = 40;

		i += 1.0f;
	}
}

void key_callBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		reset = true;
	}
}

ProgramHandler::ProgramHandler() : m_reset(false)
{
	std::cout << "Program Init" << std::endl;
	createPendulums();
	resetPendulums();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	m_window = glfwCreateWindow(1280,720,"Double Pendulum",NULL,NULL);

	if(m_window == NULL)
	{
		std::cout <<"ERRROR: Failed to create glfw window\n";
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: failed to get GL functions\n";
		exit(EXIT_FAILURE);
	}	

	glfwSwapInterval(0);
	glfwSetKeyCallback(m_window,&key_callBack);

	//compute shader
	m_compute_shader.createProgram();
	m_compute_shader.attachCompShader("res/shaders/compute_shader.glsl");
	m_compute_shader.linkProgram();

	//framebuffer
	m_framebuffer 		=	FrameBuffer("texture framebuffer");

	//textures
	m_lines_texture 	= 	Texture(1280,720);
	m_points_texture	=	Texture(1280,720);
	
	//vaos,vbos,ebos...
	//Lines buffers
	GLCALL(	glGenVertexArrays(1,&m_lines_context.vao)	);

	GLCALL(	glGenBuffers(1, &m_lines_context.vbo)	);
	GLCALL( glGenBuffers(1,&m_lines_context.ssbo)	);
	GLCALL(	glGenBuffers(1, &m_lines_context.ebo)	);

	GLCALL(	glBindVertexArray(m_lines_context.vao)	);
	GLCALL(	glBindBuffer(GL_SHADER_STORAGE_BUFFER,m_lines_context.ssbo)	);
	GLCALL( glBufferData(GL_SHADER_STORAGE_BUFFER,sizeof(Pendulum) * m_max_pendulums,m_pendulums.data(),GL_DYNAMIC_DRAW)	);
	GLCALL(	glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,m_lines_context.ssbo)	);
	GLCALL(	glBindBuffer(GL_ARRAY_BUFFER,m_lines_context.vbo)	);
	GLCALL(	glBufferData(GL_ARRAY_BUFFER,sizeof(float) * 6 * m_max_pendulums,NULL,GL_DYNAMIC_DRAW)	);
	GLCALL( glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_lines_context.vbo)	);
	GLCALL( glEnableVertexAttribArray(0)	);
	GLCALL(	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0)	);// vertex v_pos attrib

	//drawElements line indices
	std::vector<uint32_t> line_indices;
	for(int i = 0; i < m_max_pendulums; i++)
	{
		line_indices.push_back(3 * i + 0);
		line_indices.push_back(3 * i + 1);
		line_indices.push_back(3 * i + 1);
		line_indices.push_back(3 * i + 2);
	}

	GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lines_context.ebo)	);
	GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, line_indices.size() * sizeof(uint32_t),line_indices.data(),GL_STATIC_DRAW)	);

	//lines shader
	m_lines_shader.createProgram();
	m_lines_shader.attachVertShader("res/shaders/lines_vert_shader.glsl");
	m_lines_shader.attachFragShader("res/shaders/lines_frag_shader.glsl");
	m_lines_shader.linkProgram();

	//points buffers
	GLCALL(	glGenVertexArrays(1,&m_points_context.vao)	);
	GLCALL(	glBindVertexArray(m_points_context.vao)		);
	
	//using the same buffer and buffer data from drawing lines
	m_points_context.vbo = m_lines_context.vbo;

	GLCALL( glBindBuffer(GL_ARRAY_BUFFER,m_points_context.vbo)	);
	GLCALL(	glEnableVertexAttribArray(0)	);
	GLCALL(	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*) (4 * sizeof(float)))	);

	//not using element buffer nor ssbo
	m_points_context.ebo = 0;	
	m_points_context.ssbo = 0;

	//points shader
	m_points_shader.createProgram();
	m_points_shader.attachVertShader("res/shaders/points_vert_shader.glsl");
	m_points_shader.attachFragShader("res/shaders/points_frag_shader.glsl");
	m_points_shader.linkProgram();

	//points blend shader
	m_blend_shader.createProgram();
	m_blend_shader.attachVertShader("res/shaders/blend_vert_shader.glsl");
	m_blend_shader.attachFragShader("res/shaders/blend_frag_shader.glsl");
	m_blend_shader.linkProgram();

	//screen quad
	m_quad_screen.init();

	//screen shader
	m_screen_shader.createProgram();
	m_screen_shader.attachVertShader("res/shaders/screen_vert_shader.glsl");
	m_screen_shader.attachFragShader("res/shaders/screen_frag_shader.glsl");
	m_screen_shader.linkProgram();
	
	//set uniforms
	//lines
	m_lines_shader.use();
	m_lines_shader.setUniform4fv("u_colors",m_num_pendulums,m_pColors);

	//blend points
	m_blend_shader.use();
	m_blend_shader.setUniform1i("t_points",0);

	//points
	m_points_shader.use();
	m_points_shader.setUniform4fv("u_colors",m_num_pendulums,m_pColors);

	//screen
	m_screen_shader.use();
	m_screen_shader.setUniform1i("t_lines",0);
	m_screen_shader.setUniform1i("t_points",1);

	glPointSize(3);



	//GLCALL(	glEnable(GL_BLEND)	);
	//GLCALL( glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA)	);
}
	

///Program main loop
void ProgramHandler::run()
{
	std::cout << "Program running" << std::endl;

	glfwSetTime(0);
	float deltaTime = 0,currentFrame = 0,lastFrame = 0;

	while(!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();



		currentFrame = glfwGetTime();
    	deltaTime = currentFrame - lastFrame;
    	lastFrame = currentFrame;
	
		static float compTimer = 0;
		compTimer += deltaTime;

		
		//compute shader
		m_compute_shader.use();
		m_compute_shader.setUniform1f("deltaTime",deltaTime);
		GLCALL(	glDispatchCompute(m_num_pendulums,1,1)	);	
 		GLCALL(	glMemoryBarrier(GL_ALL_BARRIER_BITS)	);


		//draw lines to texture
		m_framebuffer.bind();
		m_framebuffer.bindTexture(m_lines_texture.getId());

		GLCALL(	glBindVertexArray(m_lines_context.vao)	);
		GLCALL(	glBindBuffer(GL_ARRAY_BUFFER, m_lines_context.vbo)			);
		GLCALL(	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lines_context.ebo)	);

		m_lines_shader.use();

		GLCALL(	glClearColor(0,0,0,1)	);
		GLCALL( glClear(GL_COLOR_BUFFER_BIT)	);		
		GLCALL(	glDrawElements(GL_LINES,m_num_pendulums * 4,GL_UNSIGNED_INT,NULL)	);

		//fade points
		m_quad_screen.bindAll();
		m_framebuffer.bindTexture(m_points_texture.getId());
		m_points_texture.bind(0);
		m_blend_shader.use();
		GLCALL( glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL)	);	

	
		//draw points to texture
		m_framebuffer.bindTexture(m_points_texture.getId());

		GLCALL( glBindVertexArray(m_points_context.vao)	);
		GLCALL(	glBindBuffer(GL_ARRAY_BUFFER,m_points_context.vbo)	);
		m_points_shader.use();
		m_points_shader.setUniform4f("u_color",std::vector<float>({0,0,1,1}));	

		if(reset == true)
		{
			resetPendulums();
			GLCALL(	glBindBuffer(GL_SHADER_STORAGE_BUFFER,m_lines_context.ssbo)	);
			GLCALL(	glBufferSubData(GL_SHADER_STORAGE_BUFFER,0,sizeof(Pendulum) * m_pendulums.size(),m_pendulums.data()	));
			GLCALL(	glClear(GL_COLOR_BUFFER_BIT)	);
			reset = false;
		}

		GLCALL(	glDrawArrays(GL_POINTS, 0, m_num_pendulums)	);		

		
		//default framebuffer
		m_framebuffer.unBind();
		m_quad_screen.bindAll();
		m_screen_shader.use();

		m_lines_texture.bind(0);
		m_points_texture.bind(1);

		GLCALL(	glClearColor(0,0,0,1)	);
		GLCALL(	glClear(GL_COLOR_BUFFER_BIT)	);
		GLCALL(	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL)	);

		glfwSwapBuffers(m_window);
	}

}

ProgramHandler::~ProgramHandler()
{
	std::cout << "Program terminating" << std::endl;
}

