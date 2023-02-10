#pragma once
#include <Component.h>
#include <Application.h>
#include <graphics/Shader.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

//https ://learnopengl.com/In-Practice/Text-Rendering

class TextRendering : public Component {
public:

	TextRendering();
	~TextRendering();
	void renderText(Shader* shader, std::string text, float x, float y, float scale, glm::vec3 color);



private:
	Shader* m_shader;
};