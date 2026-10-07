#include "ShaderProgram.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* win);

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Handle mouse position
void mouse_callback(GLFWwindow* win, double xposIn, double yposIn);

// Handle mouse scroll
void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);

const int SCR_WIDTH = 640;
const int SCR_HEIGHT = 480;

// time
float lastTime{}, deltaTime{};

// lighting
glm::vec3 lightPos(0.6f, 0.5f, 1.0f);

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firsMouse = true;
float yaw = -90.0f; //since yaw 0.0 result to direction to right
float pitch = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float fov = 45.0f;

int main(void)
{

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Image Display", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);  /* Make window's context current */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (glewInit() != GLEW_OK)
		std::cout << "Error! at GLEW " << std::endl;

	// Get the OPENGL VERSION 
	std::cout << glGetString(GL_VERSION) << std::endl;


	// configure global opengl state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	// world space positions of our cubes
	//glm::vec3 cubePositions[] = {
	//	glm::vec3(0.1f,  0.4f,  0.3f),
	//	glm::vec3(2.0f,  5.0f, -15.0f),
	//	glm::vec3(-1.5f, -2.2f, -2.5f),
	//	glm::vec3(-3.8f, -2.0f, -12.3f),
	//	glm::vec3(2.4f, -0.4f, -3.5f),
	//	glm::vec3(-1.7f,  3.0f, -7.5f),
	//	glm::vec3(1.3f, -2.0f, -2.5f),
	//	glm::vec3(1.5f,  2.0f, -2.5f),
	//	glm::vec3(1.5f,  0.2f, -1.5f),
	//	glm::vec3(-1.3f,  1.0f, -1.5f)
	//};

	unsigned int cubeVAO, VBO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//// color attributes								

	// texture cordinate							
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	ShaderProgram sCubeShader("src/01_materials.shader");
	ShaderProgram sLightCubeShader("src/01_lightCube.shader");

;


	while (!glfwWindowShouldClose(window)) { /* Loop until the user closes win */


		// per-frame time logic
		// --------------------
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// input -----
		processInput(window);

		/* Render here */
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// be sure to activate shader when setting uniforms/drawing objects
		sCubeShader.useProgram();
		sCubeShader.SetVec3("light.position", lightPos);
		sCubeShader.SetVec3("viewPos", camPos);

		// light properties
		glm::vec3 lightColor;
		lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
		lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
		lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		sCubeShader.SetVec3("light.ambient", ambientColor);
		sCubeShader.SetVec3("light.diffuse", diffuseColor);
		sCubeShader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

		// Material properties
		sCubeShader.SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		sCubeShader.SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		sCubeShader.SetVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't
		sCubeShader.SetFloat("material.shininess", 32.0f);

		// view/projection transformation
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	
		glm::mat4 view = glm::lookAt(camPos, camPos + camFront, camUp);
		sCubeShader.SetMat4("projection", projection);
		sCubeShader.SetMat4("view", view);

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		float rotateAngle = (float)glfwGetTime() * 12.0f;
		model = glm::rotate(model, glm::radians(rotateAngle), glm::vec3(0, 1, 0));
		sCubeShader.SetMat4("model", model);

		// render cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// also draw the lamp object
		sLightCubeShader.useProgram();
		sLightCubeShader.SetMat4("projection", projection);
		sLightCubeShader.SetMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
		sLightCubeShader.SetMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	

		glfwSwapBuffers(window); /* Swap front and back buffers */
		glfwPollEvents(); /* Poll for and process events */
	}


	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* win) {

	const float camSpeed = static_cast<float>(deltaTime);

	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);

	if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
		camPos += camSpeed * camFront;

	if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
		camPos -= camSpeed * camFront;

	if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
		camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;

	if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* win, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firsMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firsMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change value a preffered
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screens doesn't flip
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(front);

}

void scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f) fov = 1.0f;
	if (fov > 45.0f) fov = 45.0f;
}

