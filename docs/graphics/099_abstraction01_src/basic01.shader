##vertex =========================================
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 tColor;
uniform mat4 model;

void main(){

	gl_Position =  model * vec4(aPos, 1.0);
	tColor = aColor;
}

##fragment =======================================
#version 330 core

out vec4 FragColor;
in vec3 tColor;


void main(){
	FragColor = vec4(tColor, 1.0f);
}