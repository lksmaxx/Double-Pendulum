#include <ProgramHandler/ProgramHandler.hpp>

int main()
{

	ProgramHandler *program = new ProgramHandler();

	program->run();

	delete program;

	glfwTerminate();

	return 0;
}
