/*
 * @Author: BOICHARD Hugo 
 * @Date: 2021-12-07 17:30:21 
 * @Last Modified by:   Boichard Hugo 
 * @Last Modified time: 2021-12-07 17:30:21 
 */

#include <iostream>
#include <GL/glew.h>
#include "Model.hpp"
#include "Constants.hpp"

Model::~Model()
{
	// When the model is destroyed, we free all the allocated buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}

/// <summary>
/// Initialize the model
/// </summary>
/// <returns>Return true if the model has initialized correctly. Return false otherwise.</returns>
bool Model::Init()
{
	int success;
	char infoLog[512];
	const char* vertexShaderSource = this->vertexShaderSource.c_str();
	const char* fragmentShaderSource = this->fragmentShaderSource.c_str();

	// We create and compile a shader for the vertices of the triangles
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "Vertex shader compilation error: %s\n", infoLog);
		return false;
	}

	// We create and compile a fragment shader for the colors of the triangles
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Fragment shader compilation error: %s\n", infoLog);
		return false;
	}

	// We combine the vertex and the fragment shader in a program shader
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "Shader program compilation error: %s\n", infoLog);
		return false;
	}

	// We delete the vertex and the fragment shader because we don't need them anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// We create a vertices array for the triangles of the model
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(float), &verticesData[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

/// <summary>
/// Draw the model
/// </summary>
void Model::Draw()
{
	// We use the model shader and vertices
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	// We draw the model triangles
	glDrawArrays(GL_TRIANGLES, 0, triangleCount * 3);
}