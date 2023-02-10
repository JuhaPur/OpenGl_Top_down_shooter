#include <graphics/Shader.h>
#include <kgfw/GLUtils.h>
#include <Entity.h>
#include <Transform.h>


Shader::Shader(const char* const vertexShaderString, const char* const fragmentShaderString) : Transform(m_parent) {
	
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	checkGLError();
	glShaderSource(vertexShader, 1, &vertexShaderString, NULL);
	checkGLError();
	glCompileShader(vertexShader);
	checkGLError();


	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	checkGLError();
	if (!success) {
		// If failed, get error string using glGetShaderInfoLog-function.
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		checkGLError();
		printf("ERROR: Shader compilation failed: \"%s\"\n", infoLog);
	}

	// Create and compile fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	checkGLError();
	glShaderSource(fragmentShader, 1, &fragmentShaderString, NULL);
	checkGLError();
	glCompileShader(fragmentShader);
	checkGLError();
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	checkGLError();
	if (!success) {
		// If failed, get error string using glGetShaderInfoLog-function.
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		checkGLError();
		printf("ERROR: Shader compilation failed: \"%s\"\n", infoLog);
	}

	// link shaders
	m_shaderProgram = glCreateProgram();
	checkGLError();
	glAttachShader(m_shaderProgram, vertexShader);
	checkGLError();
	glAttachShader(m_shaderProgram, fragmentShader);
	checkGLError();
	glLinkProgram(m_shaderProgram);
	checkGLError();
	// check for linking errors
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	checkGLError();
	if (!success) {
		// If failed, get error string using glGetProgramInfoLog-function.
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		checkGLError();
		printf("ERROR: Shader link failed: \"%s\"\n", infoLog);
	}

	// After linking, the shaders can be deleted.
	glDeleteShader(vertexShader);
	checkGLError();
	glDeleteShader(fragmentShader);
	checkGLError();
}

Shader::~Shader() {
	glDeleteProgram(m_shaderProgram);
}


void Shader::bind() {
	glUseProgram(m_shaderProgram);
	
}

void Shader::setUniform(const std::string& name, float x, float y, float z) {
	GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
	if (location >= 0) {
		glUniform3f(location, x, y, z);
	}

}

