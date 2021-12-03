#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define WINDOW_NAME "CGAssignment4 - Hugo Boichard"
#define SUCCESS_RETURN 0
#define ERROR_RETURN 1

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glFlush();
}

void initTriangle()
{
	unsigned int VBO, vertexShader, fragmentShader, shaderProgram;
	int success;
	char infoLog[512];
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
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "Vertex shader compilation error: %s\n", infoLog);
		exit(ERROR_RETURN);
	}

	// We create and compile a fragment shader for the color of the triangle
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Fragment shader compilation error: %s\n", infoLog);
		exit(ERROR_RETURN);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "Shader program compilation error: %s\n", infoLog);
		exit(ERROR_RETURN);
	}

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

void initCube()
{
	unsigned int VBO, vertexShader, fragmentShader, shaderProgram;
	int success;
	char infoLog[512];
	float vertices[] = {
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
	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"uniform mat4 MVP;\n"
		"void main()\n"
		"{\n"
			"gl_Position = MVP * vec4(aPos, 1);\n"
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
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "Vertex shader compilation error: %s\n", infoLog);
		exit(ERROR_RETURN);
	}

	// We create and compile a fragment shader for the color of the triangle
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Fragment shader compilation error: %s\n", infoLog);
		exit(ERROR_RETURN);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "Shader program compilation error: %s\n", infoLog);
		exit(ERROR_RETURN);
	}

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

	////////////////////////////////////////////////////////////////////////////////

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	////////////////////////////////////////////////////////////////////////////////
}

void initOpenGLContext(int argc, char** argv)
{
	// Glut and window initialization
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2);
	glutCreateWindow(WINDOW_NAME);
	glutDisplayFunc(display);

	// Glew initialization
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Glew initialization error: %s\n", glewGetErrorString(err));
		exit(ERROR_RETURN);
	}

	// Opengl initialization
	glClearColor(0.098f, 0.098f, 0.098f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void init(int argc, char** argv)
{
	initOpenGLContext(argc, argv);
	initTriangle();
	//initCube();
}

int main(int argc, char** argv)
{
	init(argc, argv);
	glutMainLoop();
	return SUCCESS_RETURN;
}
