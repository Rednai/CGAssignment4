/*
 * @Author: BOICHARD Hugo 
 * @Date: 2021-12-07 17:30:32 
 * @Last Modified by: Boichard Hugo
 * @Last Modified time: 2021-12-07 17:33:42
 */

#include "Application.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Constants.hpp"

Application::~Application()
{
	// We delete all the models when the application is destroyed to free the memory
	for (Model* model : models)
		delete model;
}

/// <summary>
/// Initialize the application
/// </summary>
/// <returns>Return true if the application has initialized correctly. Return false otherwise.</returns>
bool Application::Init()
{
	// GLFW3 INITIALIZATION
	if (!glfwInit())
	{
		fprintf(stderr, "Glfw3 initialization error.\n");
		return false;
	}

	// We create a new render window
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// We enable VSYNC
	glfwSwapInterval(1);

	// Glew initialization
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Glew initialization error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		return false;
	}

	// OPENGL INITIALIZATION
	// We set the background color
	glClearColor(0.098f, 0.098f, 0.098f, 1.0f);
	// We enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// IMGUI INITIALIZATION
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// MODELS INITIALIZATION
	for (Model* model : models)
		if (!model->Init())
			return false;

	return true;
}

/// <summary>
/// Launch the render loop of the application
/// </summary>
void Application::Loop()
{
	// While the window is not closed
	while (!glfwWindowShouldClose(window))
	{
		// We clear the render buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// We setup the imgui frame for the model selection
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// We draw the selected model
		models[selectedModel]->Draw();

		// We fill the imgui window with the elements to select a model
		ImGui::Begin("Models");
		ImGui::Combo("Displayed model", &selectedModel, modelsNames, IM_ARRAYSIZE(modelsNames));
		ImGui::End();

		// We render the imgui frame
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// We get the user's inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// We call these functions to unload imgui when the window is closed
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// We call this function to unload glfw when the window is closed
	glfwTerminate();
}
