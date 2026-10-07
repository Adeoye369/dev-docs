#include "ShaderProgram.h"
#include "Texture.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Image Display", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwMakeContextCurrent(window);  /* Make window's context current */

	if (glewInit() != GLEW_OK)
		std::cout << "Error! at GLEW " << std::endl;

	// Get the OPENGL VERSION 
  /*  std::cout << glGetString(GL_VERSION) << std::endl;
*/


	float vertices[] = {
		// positions        // texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top left 
	};

	unsigned int pos_index[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	unsigned int va_id, vb_id, ib_id;
	glGenVertexArrays(1, &va_id);
	glBindVertexArray(va_id);

	glGenBuffers(1, &vb_id);
	glBindBuffer(GL_ARRAY_BUFFER, vb_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pos_index), pos_index, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);					
	//// color attributes								
				
	// texture cordinate							
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	Texture tex1("imgs/download.jpg");
	Texture tex2("imgs/avatar200.jpg");

	ShaderProgram sProg("src/basic.shader");

	sProg.useProgram();
	sProg.SetInt("texture1", 0);
	sProg.SetInt("texture2", 1);

	while (!glfwWindowShouldClose(window)) { /* Loop until the user closes win */

		/* Render here */

		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(va_id);

		tex1.Bind();
		tex2.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); /* Swap front and back buffers */

		glfwPollEvents(); /* Poll for and process events */
	}


	glfwTerminate();
	return 0;
}