#include "Game.h"

using namespace std;

GLFWwindow* initWindow()
{
	if (!glfwInit())
		exit(-1);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		cout << "glewInit() Error!" << endl;
		exit(-1);
	}

	cout << glGetString(GL_VERSION) << endl;

	return window;
}

int main()
{
	GLFWwindow* window = initWindow();

	{
		Renderer* renderer = new Renderer;

		Game game;

		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer->Clear();

			game.OnUpdate(0.0f);
			game.OnRender(renderer);
			game.Events(window);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}