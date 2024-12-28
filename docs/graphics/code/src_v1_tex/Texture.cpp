#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int Texture::texture_count = 0;

Texture::Texture(std::string texturePath) {

	texture_count ++;

	// Switch the OpenGl texture, i.e. (GL_TEXTURE0 -> GLTEXTURE1 -> GL_TEXTURE2 ...)
	//  if more texture detected
	if (texture_count > 1 ) 
		m_glTexture_num = m_glTexture_num + texture_count - 1;

	// Load and create image
	texture_id;
	// texture 1
	// ---------
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::Bind() const
{
	// bind textures on corresponding texture units

	glActiveTexture(m_glTexture_num);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}