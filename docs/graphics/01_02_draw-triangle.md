# Drawing a Triangle in OpenGL

## Passing Vertex Data to OpenGL
Basic idea is I want to define a bunch of data which represent my triangle. I want to put it in my GPU VRAM . Then issue a draw call openGL from the CPU to GPU etc.

When you generate anything in openGL, it returns an **id** whether its vertex buffer, vertex Array, Shader etc.

```c++

 //Param: 
 //n: int {number of buffers}, 
 // buffer : GLuint(unsigned int) - Unique id to identify the buffer
  unsigned int vb_id;
 glGenBuffers(1, &vb_id);

```

Basically, selecting the buffer and how to use it

```cpp
// GL_ARRAY_BUFFER means it is a contain of array 
// It can be use to do so many other this like store texture data etc
glBindBuffer(GL_ARRAY_BUFFER, vb_id);
```

Next is, Put data into the buffer(container), specify how large it

```c++
// void glBufferData(
// GLenum target - what type of buffer(here it container of array)
// GLsizeiptr size - size of pointer,
// const GLvoid * data - values container to store 
// GLenum usage - how to draw? not sure

 glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), position, GL_STATIC_DRAW);
```

## Telling OpenGL how to use the data

The Next Phase is being able to tell openGL how to read the data, How our data is laid out.

### Creating shader in Opengl

This function handles reading the shader source from string and compiling it with opengl. It then returns the shader id.
The same function is used for both vertex and fragment shader

```c++

static unsigned int CompileShader(unsigned int type, const std::string& source) {

    GLuint sh_id = glCreateShader(type);

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

        std::cout << (type ==GL_VERTEX_SHADER ? "vertex":"fragment" ) << " Shader Error:  \n" << msg << "\n";
        std::cout << msg << std::endl;
        glDeleteShader(sh_id);
        return 0;
    }
    return sh_id;
}// end CompileShader
```

## Creating program in Opengl

This function is kinda similar to shader one but this create the shader program after get the both the shader id for the vertex and fragment shader.

```c++
static unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader) {
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
```

### Initiating and create Vertex

The next phase will be initiating drawing and stuff

```c++
    float vertex_positions[8] = {
        -0.8f, -0.9f, // pos 1
        0.2f, 0.7f, // pos 2
        0.3f, -0.5f, // pos 3
         0.7f, 0.7f, // pos 4
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertex_positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
```

Then we create the shader and read it with the function we specified

```c++
std::string vShader =
    R"glsl(
        #version 330 core
        layout(location = 0) in vec4 position;
        void main()
        {
            gl_Position = position;
        }
    )glsl";

std::string fShader =
    R"glsl(
     #version 330 core
     layout(location = 0) out vec4 color;
     void main()
     {
        color = vec4(1.0, 0.5, 0.3, 1.0);
     }
      )glsl";

unsigned int shader = CreateShader(vShader, fShader);
glUseProgram(shader);
```

The final step is to go to our loop and then make the draw call

```c++ hl_lines="6-9"
/* Loop until the user closes the window */
while (!glfwWindowShouldClose(window))
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // glDrawArrays(GL_TRIANGLE_STRIP, 0,4 ); // draw  four point
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

```

Your output should be something like this

![alt text](img/image-9.png)

you can find the source code [here](./code/triangle-basic-code.cpp){target=blank}