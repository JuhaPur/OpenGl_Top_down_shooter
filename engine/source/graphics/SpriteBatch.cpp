#include <graphics/SpriteBatch.h>
#include <kgfw/GLUtils.h>	// Include GLUtils for checkGLError
#include <graphics/Shader.h>
#include <Transform.h>
#include <Entity.h>

SpriteBatch::SpriteBatch() : Transform(m_parent)
	, m_positions()
	, m_texCoords()
	, m_needUpdateBuffers(true)
	, m_positionsVbo(0)
	, m_texCoordsVbo(0)
	, m_vao(0) {
	// Create Vertex Array Object
	glGenVertexArrays(1, &m_vao);
	checkGLError();

	// Create Vertex Buffer Object
	glGenBuffers(1, &m_positionsVbo);
	checkGLError();

	glGenBuffers(1, &m_texCoordsVbo);
	checkGLError();
}

SpriteBatch::~SpriteBatch() {
	// Delete Vertex Buffer Object
	glDeleteBuffers(1, &m_positionsVbo);
	//checkGLError();

	// Delete Vertex Buffer Object
	glDeleteBuffers(1, &m_texCoordsVbo);
	//checkGLError();

	// Delete Vertex Array Object
	glDeleteVertexArrays(1, &m_vao);
	//checkGLError();
}


void SpriteBatch::clear() {
	m_positions.clear();
	m_texCoords.clear();
	m_needUpdateBuffers = true;
}

void SpriteBatch::addSprite(
	const glm::mat4 & modelMatrix,
	const glm::mat4 & viewMatrix,
	const glm::mat4 & projectionMatrix) {
	// Vertices to draw a triangle.
	float dx = 0.5f;
	float dy = 0.5f;
	glm::mat4 MVP = projectionMatrix * glm::inverse(viewMatrix) * modelMatrix;
	m_positions.push_back(MVP * glm::vec4(-dx, -dy, 0.0f, 1.0f));	// left-bottom
	m_positions.push_back(MVP * glm::vec4(dx, -dy, 0.0f, 1.0f));	// right-bottom
	m_positions.push_back(MVP * glm::vec4(dx,  dy, 0.0f, 1.0f));	// top-right
	m_positions.push_back(MVP * glm::vec4(-dx, -dy, 0.0f, 1.0f));	// left-bottom
	m_positions.push_back(MVP * glm::vec4(dx,  dy, 0.0f, 1.0f));	// top-right
	m_positions.push_back(MVP * glm::vec4(-dx,  dy, 0.0f, 1.0f));	// top-left

	m_texCoords.push_back(glm::vec2(0.0f, 1.0f));	// left-bottom 
	m_texCoords.push_back(glm::vec2(1.0f, 1.0f));	// right-bottom 
	m_texCoords.push_back(glm::vec2(1.0f, 0.0f));	// top-right 
	m_texCoords.push_back(glm::vec2(0.0f, 1.0f));	// left-bottom 
	m_texCoords.push_back(glm::vec2(1.0f, 0.0f));	// top-right 
	m_texCoords.push_back(glm::vec2(0.0f, 0.0f));	// top-left  
	m_needUpdateBuffers = true;
}

void SpriteBatch::render(Shader * shader, GLuint textureId) {
	if (m_positions.size() == 0) {
		return;
	}

	if (m_needUpdateBuffers) {
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then 
		// configure vertex attributes(s).
		glBindVertexArray(m_vao);
		checkGLError();

		// Set buffer data to m_vbo-object (bind buffer first and then set the data)
		glBindBuffer(GL_ARRAY_BUFFER, m_positionsVbo);
		checkGLError();
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_positions.size(), &m_positions[0], GL_STATIC_DRAW);
		checkGLError();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		checkGLError();
		glEnableVertexAttribArray(0);
		checkGLError();

		// Set buffer data to m_texCoordsVbo-object (bind buffer first and then set the data)
		glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsVbo);
		checkGLError();
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_texCoords.size(), &m_texCoords[0], GL_STATIC_DRAW);
		checkGLError();
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		checkGLError();
		glEnableVertexAttribArray(1);
		checkGLError();

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex 
		// attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		checkGLError();

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this
		// VAO, but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray
		// anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
		checkGLError();
		m_needUpdateBuffers = false;
	}

	// Bind the shader
	shader->bind();

	// Set texture, if set
	if (textureId > 0) {
		shader->setUniform("texture0", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	// Seeing as we only have a single VAO there's no need to bind it every time,
	// but we'll do so to keep things a bit more organized.
	glBindVertexArray(m_vao);
	checkGLError();
	// Draw 6 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_positions.size());
	checkGLError();
}
