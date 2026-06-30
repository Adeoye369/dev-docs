#pragma once
#include <iostream>
#include <GL/glew.h>

class Texture
{
private:
	unsigned int texture_id; // Load and create image
	unsigned int m_glTexture_num{ GL_TEXTURE0 };
	
public:
	static int texture_count;
	Texture(std::string texturePath);

	void Bind(const int slot = 0) const;
};

