
# Code documentation for Stencil testing

## Main.cpp

```cpp
#include <iostream>

#include <sstream>
#include <fstream>
#include <string>

#include "Renderer.h"
#include "PrimitiveMesh.h"
#include "Camera.h"


class RenderTriangle : public Renderer {

public:
	Renderer::Renderer;

	unique_ptr<GraphicObject> rectObject;
	unique_ptr<GraphicObject> cubeObject;

	Shader* shaderSingleColor;


	void setupDraw() override{
		Renderer::setupDraw();


		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


			//=============== Rectangle Object ==================================


		vector<VertexInfo> rectMesh;
			// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
			VertexInfo::attribComponentCount = { 3,  2 };
			rectMesh.push_back({ 5.0f, -0.5f,  5.0f,  2.0f, 0.0f});
			rectMesh.push_back({-5.0f, -0.5f,  5.0f,  0.0f, 0.0f});
			rectMesh.push_back({-5.0f, -0.5f, -5.0f,  0.0f, 2.0f});

			rectMesh.push_back({ 5.0f, -0.5f,  5.0f,  2.0f, 0.0f});
			rectMesh.push_back({-5.0f, -0.5f, -5.0f,  0.0f, 2.0f});
			rectMesh.push_back({ 5.0f, -0.5f, -5.0f,  2.0f, 2.0f});


		 
		// ================== Rectangle Object Draw =================
		rectObject = make_unique<GraphicObject>(rectMesh);
		rectObject->initShader("src/basic01.shader");
		rectObject->initTexture("images/picture186.png");


		// ================= Cube Object Draw =======================	
		cubeObject = make_unique<GraphicObject>(GetCubeMesh());
		cubeObject->initShader("src/basic01.shader");
		cubeObject->initTexture("images/wall.jpg");

		// ================= Single color Shader ====================
		shaderSingleColor = new Shader("src/02_stencil_single_color.shader");


	}

	void draw(GLFWwindow* win) override {
		Renderer::draw(win);
		
		// per-frame time logic
 // --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(win, deltaTime);

		glClearColor(0.1f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);



		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = cam.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(cam.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		
		shaderSingleColor->setMat4("u_view", view);
		shaderSingleColor->setMat4("u_projection", projection);


		// draw floor as normal, 
		// but don't write the floor to the stencil buffer, we only care about the containers. 
		// We set its mask to 0x00 to not write to the stencil buffer.
		glStencilMask(0x00);

		rectObject->initMVP(view, projection);
		rectObject->scale(8.0f);
		rectObject->bindTexture();
		rectObject->draw();

		// 1st. render passm draw objects as normal,
		// writing to the stencil buffer
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		
		// Draw the first cube
		cubeObject->useShader(0);
		cubeObject->initMVP(view, projection);
		cubeObject->translate(glm::vec3(-1.0f, 0.0f, -1.0f));
		cubeObject->bindTexture();
		cubeObject->draw();

		cubeObject->resetModel();
		cubeObject->translate(glm::vec3(1.0f, 0.0f, 0));
		cubeObject->rotate((float)glfwGetTime()*30.0f, glm::vec3(1, 0, 0));
		cubeObject->draw();


		// 2nd render pass : 
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		cubeObject->addShader(shaderSingleColor);
		cubeObject->useShader(1);

		float scaleFactor = 1.1f;
		
		cubeObject->resetModel();
		cubeObject->translate(glm::vec3(-1.0f, 0.0f, -1.0f));
		cubeObject->scale(scaleFactor);
		cubeObject->draw();

		cubeObject->resetModel();
		cubeObject->translate(glm::vec3(1.0f, 0, 0));
		cubeObject->rotate((float)glfwGetTime() * 30.0f, glm::vec3(1, 0, 0));
		cubeObject->scale(scaleFactor);
		cubeObject->draw();

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);



	}

	virtual ~RenderTriangle(){
		delete shaderSingleColor;
		shaderSingleColor = nullptr;
	}
};



int main()
{

	RendererWindow rendererWindow(800, 600, "some title");

	RenderTriangle drawObjects;
	drawObjects.setupDraw();

	while (!rendererWindow.mainloop()) {

		drawObjects.draw(rendererWindow.getWindow());

		rendererWindow.swapBuffers();
		rendererWindow.pollEvents();
	}


	
}
```


## GraphicObject.h

```cpp

#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

using std::vector, std::cout, std::endl, std::string, std::unique_ptr, std::make_unique;


struct VertexInfo {

	// store the actual vertex data
	vector<float> vertex{};

	// attribute count as in the coordinate x, y, z
	// index           0            1           2
	// e.g count       3            2           3
	//             0.5, 0.2, 0.4,  1.0, 1.0,  0.5, 0.5, 0.0
	static inline vector<unsigned int> attribComponentCount;

	// total count of layout
	static inline unsigned int stride{};

	VertexInfo() = default;

	VertexInfo(std::initializer_list<float> v) : vertex(v){
		stride = vertex.size() * sizeof(float);
	}

};

class GraphicObject{
	vector<VertexInfo> verticesInfo;
	vector<float>vertices{};
	vector<unsigned int>indices{};

	unsigned int VBO{}, IBO{};

	bool hasIBO{}, hasTexture{};

	vector<Shader*> shaders;
	int currentShaderIndex = -1;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 MVP;

	void setupVBO() {

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * VertexInfo::stride, vertices.data(), GL_STATIC_DRAW);

	}

	void setupIBO() {

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * VertexInfo::stride, indices.data(), GL_STATIC_DRAW);
	
	}

	void setupObject() {

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		setupVBO();
		if(hasIBO) setupIBO();
	
		// for all layout
		int offset = 0;
		for (int i = 0; i < VertexInfo::attribComponentCount.size(); i++){
			
			// attribut component component eg. x, y => (2); x,y,z => (3),
			int attribCompCount = VertexInfo::attribComponentCount[i];
			glVertexAttribPointer(
				i,									// index
				attribCompCount,	// component count
				GL_FLOAT,							// component type
				GL_FALSE,							// Normalize?
				VertexInfo::stride,					// vertex attributes stride
				(void*)(offset * sizeof(float))); // vertex attribute offset

			glEnableVertexAttribArray(i);

			offset += attribCompCount;
		}

		glBindVertexArray(0);
	}


public:
	unsigned int VAO;
	Texture* tex1;

	GraphicObject(vector<VertexInfo> verticesInfos) {
		this->verticesInfo = verticesInfos;

		//append the vertices
		for (size_t i = 0; i < verticesInfos.size(); i++)
			vertices.insert( vertices.end(), verticesInfos[i].vertex.begin(), verticesInfos[i].vertex.end() );

		hasIBO = false;

		setupObject();
	};


	GraphicObject(vector<VertexInfo>verticesInfos, vector<unsigned int>indices) {
		this->verticesInfo = verticesInfos;

		//append the vertices
		for (size_t i = 0; i < verticesInfos.size(); i++)
			vertices.insert( vertices.end(), verticesInfos[i].vertex.begin(), verticesInfos[i].vertex.end() );


		this->indices = indices;
		hasIBO = true;

		setupObject();
	}

	// === SHADER RELATED ==============================

	// add new shader to arrays of shaders
	void initShader(const char* shaderPath){
		this->addShader( new Shader(shaderPath));

	}

	Shader* getShader(const int idx) const { 
		return shaders[idx]; 
	}

	void addShader(Shader* newShader, bool use=true) {

		shaders.push_back(newShader);
		currentShaderIndex++;

		if(use) shaders[currentShaderIndex]->useProgram();
		
	}

	void useShader(int idx) {
		currentShaderIndex = idx;
		shaders[currentShaderIndex]->useProgram();
	}

	// === TEXTURE RELATED =============================

	void initTexture(const char* texturePath) {
		hasTexture = true;
		tex1 = new Texture(texturePath);
		shaders[0]->useProgram();
		shaders[0]->setInt("texture1", 0);
	}

	void bindTexture(unsigned int slot = 0) {
		tex1->bindTexture(slot);
	}

	void unBindTexture() {
		tex1->unBindTexture();
	}



	// === MVP RELATED =========================

	void initMVP(glm::mat4 view = glm::mat4(0), glm::mat4 proj = glm::mat4(0)) {
		this->model = glm::mat4(1.0f);
		this->view = glm::mat4(1.0f);
		this->projection = glm::mat4(1.0f);


		// Should the view be set;
		if (view != glm::mat4(0))	this->view = view;
		else						this->view = glm::translate(this->view, glm::vec3(0.0f, 0.0f, -3.0f));

		// should the projection be set
		if (proj != glm::mat4(0))	this->projection = proj;
		else						this->projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

		this->setMVP(this->model, this->view, this->projection);
	
	}


	GraphicObject& setMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {

		this->model = model;
		this->view = view;
		this->projection = projection;

		//this->MVP = this->projection * this->view * this->model;

		bindVertex();
		shaders[currentShaderIndex]->useProgram();
		//objShader->setMat4("u_MVP", this->MVP);
		shaders[currentShaderIndex]->setMat4("u_model", this->model);
		shaders[currentShaderIndex]->setMat4("u_view", this->view);
		shaders[currentShaderIndex]->setMat4("u_projection", this->projection);

		return *this;
	}

	glm::mat4 getModel() const { return this->model; }
	glm::mat4 getView() const { return this->view;  }
	glm::mat4 getProjection() const { return this->projection; }

	// === TRANSFORMATIONS RELATED =========================

	void translate(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) {
		// calc. the model matrix for each object and pass it to shader before drawing

		this->model = glm::translate(this->model, position);
		shaders[currentShaderIndex]->setMat4("u_model", this->model);
	}

	void rotate(const float angle = 0.0f, glm::vec3 rotateAround = glm::vec3(0.0f, 0.0f, 1.0f)) {
		this->model = glm::rotate(this->model, glm::radians(angle), rotateAround);
		shaders[currentShaderIndex]->setMat4("u_model", this->model);
		
	}

	void scale(float x, float y, float z) {
		this->model = glm::scale(this->model, glm::vec3(x, y, z));
		shaders[currentShaderIndex]->setMat4("u_model", this->model);
	}

	void scale(float value) {
		this->scale(value, value, value);
	}

	void resetModel() {
		this->model = glm::mat4(1.0f);
	}


	void bindVertex() const {
		glBindVertexArray(VAO);
	}

	void unbindVertex()const {
		glBindVertexArray(0);
	}


	void draw(){

		// render boxes
		//this->bindVertex();
		if (hasIBO) glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
		else		glDrawArrays(GL_TRIANGLES, 0, verticesInfo.size());
		//this->unbindVertex();

	}

	~GraphicObject() {
		delete tex1;
	}
};

#endif # GRAPHICOBJECT_H
```