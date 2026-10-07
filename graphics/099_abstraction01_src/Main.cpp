#include <iostream>

#include <sstream>
#include <fstream>
#include <string>

#include "Renderer.h"


class RenderTriangle : public Renderer {

public:
	unique_ptr<GraphicObject> graphicObject;
	unique_ptr<GraphicObject> graphicObject1;

	Renderer::Renderer;

	void setupDraw() override{
		Renderer::setupDraw();

		// Vertices
		vector<VertexInfo> triangleVertices;
										// Position      // color
		triangleVertices.push_back({ -0.5f, -0.5f, 0.0f, 1.0f , 0.0f, 0.0f});
		triangleVertices.push_back({ 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f });
		triangleVertices.push_back({ 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f});


		graphicObject = make_unique<GraphicObject>(triangleVertices);
		graphicObject->initShader("src/basic01.shader");


		graphicObject1 = make_unique<GraphicObject>(triangleVertices);
		graphicObject1->initShader("src/basic02.shader");

		graphicObject->translate(glm::vec3(0.5f, 0.0f, 0.0f));
		graphicObject->rotate(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		

	}

	void draw() override {
		Renderer::draw();

		glClearColor(0.1f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Upside down triangle
	
		graphicObject->setModel();
		graphicObject->draw();
		graphicObject->unbindVertex();
		
		double time = glfwGetTime();
		float color_offset = static_cast<float>(cos(time)/2.0 + 0.5);
		graphicObject1->setModel();
		graphicObject1->objShader->setFloat("c_offset", color_offset);
		graphicObject1->draw();

		glfwSwapBuffers(win);
		glfwPollEvents();

	}

	virtual ~RenderTriangle(){
		
	}
};



int main()
{
	RenderTriangle triangle;
	triangle.init(800, 600, "some title");
	triangle.setupDraw();
	while (!glfwWindowShouldClose(triangle.getWindow()) ) {
		triangle.draw();
	}



}