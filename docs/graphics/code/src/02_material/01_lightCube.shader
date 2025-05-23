#shader vertex===============================
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model, view, projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment=================================
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}