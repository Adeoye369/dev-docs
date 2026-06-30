#pragma once
#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

	void SetInt(const char* uniform_name, int value);
	void SetInt2(const char* uniform_name, int x, int y);

	void SetFloat(const char* uniform_name, float value);
	void SetVec2(const char* uniform_name, float x, float y);
	
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const char* uniform_name, float x, float y, float z);
	
	void SetVec4(const char* uniform_name, float x, float y, float z, float w);

	void SetMat2(const char* uniform_name, const glm::mat2& mat) const;
	void SetMat3(const char* uniform_name, const glm::mat3& mat) const;
	void SetMat4(const char* uniform_name, const glm::mat4& mat) const;
	




	unsigned int getShaderID() const { return sh_id; }
	unsigned int getProgramID() const { return prog_id; }
};

