#include "ShaderProgram.h"


ShaderSource ShaderProgram::ParseShader(const std::string& filePath)
{
	enum class shType { NONE = -1, VERT = 0, FRAG = 1 };
	shType type = shType::NONE; // use to seperate lines of shaders

	std::stringstream ss[2]; // array to hold  the shaders
	std::ifstream stream(filePath); // load the file src in stream
	std::string line{}; // holder for each line

	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {

			if (line.find("vertex") != std::string::npos)
				type = shType::VERT;

			else if (line.find("fragment") != std::string::npos)
				type = shType::FRAG;

		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}// end ParseShader


unsigned int ShaderProgram::CompileShader(unsigned int type, const std::string& source) {

	sh_id = glCreateShader(type);

	const char* shader_src = source.c_str();
	glShaderSource(sh_id, 1, &shader_src, nullptr);

	glCompileShader(sh_id);

	int success;
	glGetShaderiv(sh_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		int length;
		glGetShaderiv(sh_id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(sh_id, length, &length, msg);

		/*char msg[1024];
		glGetShaderInfoLog(shader_id, 1024, NULL, msg);*/

		std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " Shader Error:  \n" << msg << "\n";
		std::cout << msg << std::endl;
		glDeleteShader(sh_id);
		return 0;
	}
	return sh_id;
}// end CompileShader


unsigned int ShaderProgram::CreateShaderProgram(const std::string& vertShader, const std::string& fragShader)
{

	prog_id = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

	glAttachShader(prog_id, vs);
	glAttachShader(prog_id, fs);

	glLinkProgram(prog_id);
	glValidateProgram(prog_id);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return prog_id;
}// end CreateShaderProgram : vs, fs

unsigned int ShaderProgram::CreateShaderProgram(const std::string& filePath) {
	ShaderSource shaderSource = ParseShader(filePath);
	return CreateShaderProgram(shaderSource.VertSource.c_str(), shaderSource.FragSource.c_str());
} // end CreateShaderProgram : filepath

ShaderProgram::ShaderProgram(const std::string& filePath) {
	CreateShaderProgram(filePath);
}

ShaderProgram::ShaderProgram(const std::string& vertShader, const std::string& fragShader) {
	CreateShaderProgram(vertShader, fragShader);
}

void ShaderProgram::useProgram() {
	glUseProgram(prog_id);
}

void ShaderProgram::SetInt(const char* uniform_string, int value){
	unsigned int uniform_id = glGetUniformLocation(prog_id, uniform_string);
	glUniform1i(uniform_id, value);
}

void ShaderProgram::SetInt2(const char* uniform_string, int x, int y)
{
	unsigned int uniform_id = glGetUniformLocation(prog_id, uniform_string);
	glUniform2i(uniform_id, x, y);
}

void ShaderProgram::SetFloat4(const char* uniform_string, float x, float y, float z, float w) {
	unsigned int uniform_id = glGetUniformLocation(prog_id, uniform_string);
	glUniform4f(uniform_id, x, y, z, w);
}
