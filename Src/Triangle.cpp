/*
 * @Author: BOICHARD Hugo 
 * @Date: 2021-12-07 17:30:13 
 * @Last Modified by:   Boichard Hugo 
 * @Last Modified time: 2021-12-07 17:30:13 
 */

#include "Triangle.hpp"

Triangle::Triangle()
{
	verticesData = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(aPos, 1.0);\n"
			"ourColor = aColor;\n"
		"};\0";
	fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
			"FragColor = vec4(ourColor, 1.0);\n"
		"};\0";
	triangleCount = 1;
}