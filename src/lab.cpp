#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "lab_processing.h"
#include "ui.h"

#define UI_WINDOW_HEIGHT	585
#define UI_WINDOW_WIDTH		395

GLFWwindow* ui;

void render()
{
	ImGui::Render();

	int display_w, display_h;
	glfwGetFramebufferSize(ui, &display_w, &display_h);

	glViewport(0, 0, display_w, display_h);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(ui);
}

void clean()
{
	cv::destroyAllWindows();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(ui);
	glfwTerminate();
}

void init_libraries()
{
	// Setup OpenGL3 context and creating UI window
	if (!glfwInit())
	{
		std::cout << "smth goes wrong, GLFW does not init :(\n";
		exit(-1);
	}

	ui = glfwCreateWindow(UI_WINDOW_WIDTH, UI_WINDOW_HEIGHT, "UI", NULL, NULL);
	glfwMakeContextCurrent(ui);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "smth goes wrong, GLEW does not init :(\n";
		exit(-1);
	}

	//	ImGui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(ui, true);
	ImGui_ImplOpenGL3_Init();

	set_window_flags();
}

int main(int argc, char* argv[])
{
	init_libraries();

	init_resources();

	while (!glfwWindowShouldClose(ui))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		draw_ui();
	
		render();
	}

	clean();
	return 0;
}
