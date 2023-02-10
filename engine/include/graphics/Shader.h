#pragma once        // Include guard. For more information, see: https://en.wikipedia.org/wiki/Pragma_once
#include <Transform.h>
#include <glad/gl.h>        // Include glad
#include <string>

class Shader : public Transform {
public:
	Shader(const char* const vertexShaderString, const char* const fragmentShaderString);
	~Shader();

	void setUniform(const std::string& name, float x, float y, float z);

	void bind();

    void setUniform(const std::string& name, const glm::mat4& m) {
		GLint loc = glGetUniformLocation(m_shaderProgram, name.c_str());
		if (loc < 0) {
			return; // Don't set the uniform value, if it not found
		}
		glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
		//checkGLError();
	}

    void setUniform(const std::string& name, float x, float y, float z, float w) {
		GLint loc = glGetUniformLocation(m_shaderProgram, name.c_str());
		if (loc < 0) {
			return; // Don't set the uniform value, if it not found
		}
		glUniform4f(loc, x, y, z, w);
		GLenum err = glGetError();
		if (err != GL_NO_ERROR) {
			glUniform3f(loc, x, y, z); // Set as 3 component value in case of 4 component set failed.
		}

		checkGLError();
	}

    void setUniform(const std::string& name, int value) {
		GLint loc = glGetUniformLocation(m_shaderProgram, name.c_str());
		if (loc < 0) {
			return; // Don't set the uniform value, if it not found
		}
		glUniform1i(loc, value);
		checkGLError();
	}

private:
	GLint m_shaderProgram;  // Handle to the shader program
	Entity* m_parent;
};
