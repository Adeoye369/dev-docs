#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>


struct ShaderSource {
    std::string VertSource;
    std::string FragSource;
};

static ShaderSource ParseShader(const std::string& filePath)
{
    enum class shType{ NONE = -1, VERT = 0, FRAG = 1};
    shType type = shType::NONE; // use to seperate lines of shaders

    std::stringstream ss[2]; // array to hold  the shaders
    std::ifstream stream(filePath); // load the file src in stream
    std::string line{}; // holder for each line

    while (getline(stream, line)) {

        if (line.find("#shader") != std::string::npos){

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
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    GLuint shader_id = glCreateShader(type);

    const char* shader_src = source.c_str();
    glShaderSource(shader_id, 1, &shader_src, nullptr);

    glCompileShader(shader_id);

    int success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    /* int length;
     glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
     char* msg = (char*)alloca(length * sizeof(char));
     glGetShaderInfoLog(shader_id, length, &length, msg);*/
    if (success == GL_FALSE) {
        char msg[1024];
        glGetShaderInfoLog(shader_id, 1024, NULL, msg);

        std::cout << " VERTEX:  \n" << msg << "\n";
    }
    return shader_id;
}// end CompileShader

static unsigned int CreateShaderProgram(const std::string& filePath) {
    ShaderSource shaderSource = ParseShader(filePath);

    // shaders compilation
    GLuint vid = CompileShader(GL_VERTEX_SHADER, shaderSource.VertSource.c_str());
    GLuint fid = CompileShader(GL_FRAGMENT_SHADER, shaderSource.FragSource.c_str());

    //Linking the program
    GLuint prog = glCreateProgram();

    glAttachShader(prog, vid);
    glAttachShader(prog, fid);

    glLinkProgram(prog);
    glValidateProgram(prog);

    glDeleteShader(vid);
    glDeleteShader(fid);

    return prog;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Tutorial 01", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << " Glew Error \n";
    }

    float vert_pos[8] = {
        0.1f, -0.4f,
        -0.7f, 0.2f,
        0.5f, 0.5f,
        0.5f, -0.5f
    };

    int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vert_pos, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0);


    //Linking the program
    GLuint prog = CreateShaderProgram("res/shader/basic.shader");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(prog);

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}