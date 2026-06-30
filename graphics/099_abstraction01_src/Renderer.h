#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

#include "GraphicObject.h"

class Renderer {

public:
	GLFWwindow* win{};
	Renderer() {}
	void init(int scr_W, int scr_H, const char* title) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		win = glfwCreateWindow(scr_W, scr_H, title, NULL, NULL);
		if (!win) {
			std::cout << "GLFW failed to load" << std::endl;
			glfwTerminate();

		}

		glfwMakeContextCurrent(win);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "GLAD failed to load" << std::endl;

		}
	}

	GLFWwindow* getWindow() {
		return win;
	}
	virtual void setupDraw() {};

	virtual void draw() {}

	virtual ~Renderer() {
		glfwTerminate();
	}


};


#endif // RENDERER_H