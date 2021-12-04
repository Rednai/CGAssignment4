#include "Application.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Constants.hpp"

Application::~Application()
{
	for (Model* model : models)
		delete model;
}

bool Application::Init()
{
	// Glfw3 and window initialization
	if (!glfwInit())
	{
		fprintf(stderr, "Glfw3 initialization error.\n");
		return false;
	}

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Glew initialization
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Glew initialization error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		return false;
	}

	// Opengl initialization
	glClearColor(0.098f, 0.098f, 0.098f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Imgui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Models initialization
	for (Model* model : models)
		if (!model->Init())
			return false;

	return true;
}

void Application::Loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		models[selectedModel]->Draw();

		ImGui::Begin("Models");
		ImGui::Combo("Displayed model", &selectedModel, modelsNames, IM_ARRAYSIZE(modelsNames));
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
