#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();
}

void initTriangle()
{
	unsigned int VBO;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(aPos, 1.0);\n"
			"ourColor = aColor;\n"
		"};\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
			"FragColor = vec4(ourColor, 1.0);\n"
		"};\0";

	// We create and compile a shader for the vertices of the triangle
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// We create and compile a fragment shader for the color of the triangle
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// We create the vertices array for the triangle
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glUseProgram(shaderProgram);
}

void initOpenGLContext(int argc, char** argv)
{
	// Glut and window initialization
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 700) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 700) / 2);
	glutCreateWindow("CGAssignment4");
	glClearColor(0.098f, 0.098f, 0.098f, 1.0f);
	glutDisplayFunc(display);

	// Glew initialization
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// TODO : handle glew errors
	}
}

void loop()
{
	glutMainLoop();
}

void init(int argc, char** argv)
{
	initOpenGLContext(argc, argv);
	initTriangle();
}

int main(int argc, char** argv)
{
	init(argc, argv);
	loop();
	return 0;
}
