#include <graphics/Texture.h>
#include <kgfw/GLUtils.h>  // Include GLUtils for checkGLError
#include <glad/gl.h>      // Include glad
#include <stb_image.h>


Texture::Texture(int width, int height, int nrChannels, const unsigned char* data)
{

	// Create texture
	glGenTextures(1, &m_textureId);
	checkGLError();
	// Bind it for use
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	checkGLError();
	// set the texture data as RGBA
	glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
	checkGLError();
	// set the texture wrapping options to repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	checkGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	checkGLError();
	// set the texture filtering to nearest (disabled filtering)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	checkGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	checkGLError();
	// enable transparency
	glEnable(GL_BLEND);
	checkGLError();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	checkGLError();
}

Texture::~Texture() {
    glDeleteTextures(1, &m_textureId);
}

GLuint Texture::getTextureId() const {
    return m_textureId;
}

