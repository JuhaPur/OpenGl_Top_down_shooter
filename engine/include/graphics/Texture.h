#pragma once
//#include <glad/gl.h>      // Include glad

class Texture {
public:
    Texture(int width, int height, int nrChannels, const unsigned char* data);
	~Texture();

    unsigned int getTextureId() const;
	
private:
    unsigned int       m_textureId;  // Texture id
};
