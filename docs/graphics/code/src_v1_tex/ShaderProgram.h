#pragma once
#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ShaderSource {
	std::string VertSource;
	std::string FragSource;
};

class ShaderProgram {
	unsigned int vbo{}, vao{};
	unsigned int sh_id{}, prog_id{}; // Shader and Program id

	ShaderSource ParseShader(const std::string& filePath);

	unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int CreateShaderProgram(const std::string& vertShader, const std::string& fragShader);

	unsigned int CreateShaderProgram(const std::string& filePath);

	void init() {};

public:
	ShaderProgram(const std::string& filePath);

	ShaderProgram(const std::string& vertShader, const std::string& fragShader);

	void useProgram();

	void SetInt(const char* uniform_string, int value);
	void SetInt2(const char* uniform_string, int x, int y);
	void SetFloat4(const char* uniform_string, float x, float y, float z, float w);



	unsigned int getShaderID() const { return sh_id; }
	unsigned int getProgramID() const { return prog_id; }
};

