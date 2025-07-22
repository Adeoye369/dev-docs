
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

using std::vector, std::cout, std::endl, std::string, std::unique_ptr, std::make_unique;


struct LayoutInfo {
	unsigned int count;
	unsigned int offset;
};

struct VertexInfo {

	// store the actual vertex data
	vector<float> vertex{};


	// attribute index of layout 
	//e.g index:		0		    1		    2
	//                position  texcoord      normal
	static inline unsigned int index{};
	
	// attribute count as in the coordinate x, y, z
	// e.g count       3            2           3
	//             0.5, 0.2, 0.4,  1.0, 1.0,  0.5, 0.5, 0.0
	vector<unsigned int> count;
	static inline vector<LayoutInfo> layoutInfo;

		// total count of layout
	static inline unsigned int stride{};

	VertexInfo() {};

	VertexInfo(std::initializer_list<float> v) : vertex(v){

		// position 2D ===============================
		if (vertex.size() == 2) {
			stride = vertex.size() * sizeof(float);
			index = 0;
			// count and offset
			layoutInfo.push_back({2, 0}); // layout position 2d
		}
		else if (vertex.size() == 4) {
			stride = vertex.size() * sizeof(float);
			index = 1;
			// count and offset
			layoutInfo.push_back({2, 0}); // layout position 2d
			layoutInfo.push_back({2, 2}); // layout texcoord
		}

		// position 3D ================================
		else if (vertex.size() == 3) {
			stride = vertex.size() * sizeof(float);
			index = 0;
			// count and offset
			layoutInfo.push_back({3,0}); // layout position 3d
		}

		// position , texcoord
		else if (vertex.size() == 5) {
			stride = vertex.size() * sizeof(float);
			index = 1;
			// count and offset
			layoutInfo.push_back({3, 0}); // layout position 3d
			layoutInfo.push_back({2, 3}); // layout texcoord
		}

		// position , color or normal
		else if (vertex.size() == 6) {
			stride = vertex.size() * sizeof(float);
			index = 1;
			// count and offset
			layoutInfo.push_back({ 3, 0 }); // layout position 3d
			layoutInfo.push_back({ 3, 3 }); // layout texcoord
		}

		// position , texcoord, normal
		else if (vertex.size() == 8) {
			stride = vertex.size() * sizeof(float);
			index = 2;
			// count and offset
			layoutInfo.push_back({3, 0}); // layout position 3d
			layoutInfo.push_back({2, 3}); // layout texcoord
			layoutInfo.push_back({3, 5}); // normal
		};
	}


};

class GraphicObject{
	vector<VertexInfo> verticesInfo;
	vector<float>vertices{};
	vector<unsigned int>indices{};

	unsigned int VBO{}, IBO{};

	bool hasIBO{};

	glm::mat4 projection{};
	glm::mat4 view{};
	glm::mat4 model{};

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
		for (int i = 0; i <= VertexInfo::index; i++){
			glVertexAttribPointer(
				i,									// index
				VertexInfo::layoutInfo[i].count,	// component count
				GL_FLOAT,							// component type
				GL_FALSE,							// Normalize?
				VertexInfo::stride,					// vertex attributes stride
				(void*)(VertexInfo::layoutInfo[i].offset * sizeof(float))); // vertex attribute offset

			glEnableVertexAttribArray(i);
		}

		glBindVertexArray(0);
	}


public:
	unsigned int VAO;
	Shader* objShader;
	std::unique_ptr <Texture> tex1, tex2;

	GraphicObject(vector<VertexInfo> verticesInfos) {
		this->verticesInfo = verticesInfos;

		//append the vertices
		for (size_t i = 0; i < verticesInfos.size(); i++)
			vertices.insert(vertices.end(), verticesInfos[i].vertex.begin(), verticesInfos[i].vertex.end());

		this->vertices = vertices;
		hasIBO = false;

		setupObject();
	};


	GraphicObject(vector<VertexInfo>verticesInfos, vector<unsigned int>indices) {
		this->verticesInfo = verticesInfos;

		//append the vertices
		for (size_t i = 0; i < verticesInfos.size(); i++)
			vertices.insert(vertices.end(), verticesInfos[i].vertex.begin(), verticesInfos[i].vertex.end());

		this->vertices = vertices;
		this->indices = indices;
		hasIBO = true;

		setupObject();
	}

	void initShader(const char* shaderPath){

	objShader = new Shader(shaderPath);

	objShader->useProgram();

	//tex1 = std::make_unique <Texture>("imgs/picture1.png");
	//tex1->bindTexture(0);

	//tex2 = std::make_unique <Texture>("imgs/picture2.png");
	//tex2->bindTexture(1);

	// objShader->setInt("texture1", 0);
	// objShader->setInt("texture2", 1);

	 this->model = glm::mat4(1.0f);
	 this->view = glm::mat4(1.0f);
	 this->projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	 this->setProjection(projection);

	}

	GraphicObject& setProjection(glm::mat4 projection = glm::mat4(1.0f))  {

		this->projection = projection;
		objShader->useProgram();
		objShader->setMat4("projection", this->projection);
		return *this;
	}

	GraphicObject& setView(glm::mat4 view = glm::mat4(1.0f)) {

		this->view = view;
		objShader->useProgram();
		objShader->setMat4("view", this->view);

		return *this;
	}

	GraphicObject& setModel(glm::mat4 model = glm::mat4(1.0f)) {

		objShader->useProgram();
		objShader->setMat4("model", this->model);

		return *this;
	}

	void translate(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) {
		// calc. the model matrix for each object and pass it to shader before drawing
		this->model = glm::translate(this->model, position);
		this->setModel();
	}

	void rotate(const float angle = 0.0f, glm::vec3 rotateAround = glm::vec3(0.0f, 0.0f, 1.0f)) {
		this->model = glm::rotate(this->model, glm::radians(angle), rotateAround);
		this->setModel();
	}

	void bindVertex() const {
		glBindVertexArray(VAO);
	}

	void unbindVertex()const {
		glBindVertexArray(0);
	}

	void draw(){

		// render boxes
		this->bindVertex();
		if (!hasIBO) glDrawArrays(GL_TRIANGLES, 0, verticesInfo.size());
		else		 glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);

	}



	~GraphicObject() {
		delete objShader;
	}

};


#endif # GRAPHICOBJECT_H