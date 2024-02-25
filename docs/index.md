# Welcome to Adeoyes Dev Docs

This is mee working to MKDocs document

## Introduction to GL

This is another intro you can have when working with OpenGL.
Compile shader those what it says it compile the shaders and much more

```c++ title="compile-shader.cpp" linenums="30" hl_lines="11 12 13 14"
static unsigned int CompileShader(unsigned int type, const std::string& source) 
{
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
```

## Parse Fragment and Vertex Shader

There are various approach to parse your shaders and you can start by creating things like `basic.shader` to serve as your default shader.

* We start by creating a struct to hold the vertex and Fragment shader
  
```c++ linenums
struct ShaderSource {
    std::string VertSource;
    std::string FragSource;
};
```



