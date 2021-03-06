/*
 * @Author: BOICHARD Hugo 
 * @Date: 2021-12-07 17:30:27 
 * @Last Modified by:   Boichard Hugo 
 * @Last Modified time: 2021-12-07 17:30:27 
 */

#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Cube.hpp"
#include "Constants.hpp"

Cube::Cube()
{
	verticesData = {
		-1.0f,-1.0f,-1.0f, 0.583f, 0.771f, 0.014f,
		-1.0f,-1.0f, 1.0f, 0.609f, 0.115f, 0.436f,
		-1.0f, 1.0f, 1.0f, 0.327f, 0.483f, 0.844f,
		 1.0f, 1.0f,-1.0f, 0.822f, 0.569f, 0.201f,
		-1.0f,-1.0f,-1.0f, 0.435f, 0.602f, 0.223f,
		-1.0f, 1.0f,-1.0f, 0.310f, 0.747f, 0.185f,
		 1.0f,-1.0f, 1.0f, 0.597f, 0.770f, 0.761f,
		-1.0f,-1.0f,-1.0f, 0.559f, 0.436f, 0.730f,
		 1.0f,-1.0f,-1.0f, 0.359f, 0.583f, 0.152f,
		 1.0f, 1.0f,-1.0f, 0.483f, 0.596f, 0.789f,
		 1.0f,-1.0f,-1.0f, 0.559f, 0.861f, 0.639f,
		-1.0f,-1.0f,-1.0f, 0.195f, 0.548f, 0.859f,
		-1.0f,-1.0f,-1.0f, 0.014f, 0.184f, 0.576f,
		-1.0f, 1.0f, 1.0f, 0.771f, 0.328f, 0.970f,
		-1.0f, 1.0f,-1.0f, 0.406f, 0.615f, 0.116f,
		 1.0f,-1.0f, 1.0f, 0.676f, 0.977f, 0.133f,
		-1.0f,-1.0f, 1.0f, 0.971f, 0.572f, 0.833f,
		-1.0f,-1.0f,-1.0f, 0.140f, 0.616f, 0.489f,
		-1.0f, 1.0f, 1.0f, 0.997f, 0.513f, 0.064f,
		-1.0f,-1.0f, 1.0f, 0.945f, 0.719f, 0.592f,
		 1.0f,-1.0f, 1.0f, 0.543f, 0.021f, 0.978f,
		 1.0f, 1.0f, 1.0f, 0.279f, 0.317f, 0.505f,
		 1.0f,-1.0f,-1.0f, 0.167f, 0.620f, 0.077f,
		 1.0f, 1.0f,-1.0f, 0.347f, 0.857f, 0.137f,
		 1.0f,-1.0f,-1.0f, 0.055f, 0.953f, 0.042f,
		 1.0f, 1.0f, 1.0f, 0.714f, 0.505f, 0.345f,
		 1.0f,-1.0f, 1.0f, 0.783f, 0.290f, 0.734f,
		 1.0f, 1.0f, 1.0f, 0.722f, 0.645f, 0.174f,
		 1.0f, 1.0f,-1.0f, 0.302f, 0.455f, 0.848f,
		-1.0f, 1.0f,-1.0f, 0.225f, 0.587f, 0.040f,
		 1.0f, 1.0f, 1.0f, 0.517f, 0.713f, 0.338f,
		-1.0f, 1.0f,-1.0f, 0.053f, 0.959f, 0.120f,
		-1.0f, 1.0f, 1.0f, 0.393f, 0.621f, 0.362f,
		 1.0f, 1.0f, 1.0f, 0.673f, 0.211f, 0.457f,
		-1.0f, 1.0f, 1.0f, 0.820f, 0.883f, 0.371f,
		 1.0f,-1.0f, 1.0f, 0.982f, 0.099f, 0.879f
	};
	vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"uniform mat4 MVP;\n"
		"void main()\n"
		"{\n"
			"gl_Position = MVP * vec4(aPos, 1);\n"
			"ourColor = aColor;\n"
		"};\0";
	fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
			"FragColor = vec4(ourColor, 1.0);\n"
		"};\0";
	triangleCount = 12;
}

bool Cube::Init()
{
	if (!Model::Init())
		return false;

	glUseProgram(shaderProgram);

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * View * Model;
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUseProgram(0);

	return true;
}
