#pragma once
#include <Transform.h>
#include <glad/gl.h>		// Include glad
#include <vector>
#include <glm/glm.hpp>
#include <Entity.h>

class Shader;

class SpriteBatch : public Transform {
public:
	SpriteBatch();
	~SpriteBatch();

	void clear();
	void addSprite(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix = glm::mat4(1.0f), const glm::mat4& projectionMatrix = glm::mat4(1.0f));
	void render(Shader* shader, GLuint textureId);


private:
	std::vector<glm::vec3>	m_positions;
	std::vector<glm::vec2>	m_texCoords;
	bool					m_needUpdateBuffers;
	GLuint					m_positionsVbo;	// Handle to positions VBO
	GLuint					m_texCoordsVbo;	// Handle to positions VBO
	GLuint					m_vao;			// Handle to VAO
	Entity*					m_parent;
};
