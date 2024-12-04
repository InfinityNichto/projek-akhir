#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

// OpenGL error handler
void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
							  GLsizei length, const GLchar *message, const void *userParam) {
	cerr << "opengl error: " << message << endl;
}

int main(int, char**) {
	// opengl setup
	if (!glfwInit()) {
		cerr << "opengl error: glfwInit failed" << endl;
		return -1;
	}

	GLFWwindow *window = glfwCreateWindow(1280, 720, "imgui demo", NULL, NULL);
	if (!window) {
		glfwTerminate();
		cerr << "opengl error: window creation failed" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // vsync
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "opengl error: loader init failed" << endl;
		return -1;
	}

	// imgui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	// main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

	    ImGui::Render();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
	}

	// cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

