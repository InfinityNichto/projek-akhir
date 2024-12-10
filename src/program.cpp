#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h>

#include "program.h"
#include "main_window.h"

#include <iostream>
using namespace std;

const int GL_WINDOW_SIZE = 1280;
const int GL_WINDOW_HEIGHT = 720;

GLFWwindow* opengl_setup() {
    if (!glfwInit()) {
        cerr << "opengl error: glfwInit failed" << endl;
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(GL_WINDOW_SIZE, GL_WINDOW_HEIGHT, "Dear ImGui - Powered by OpenGL3 + GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        cerr << "opengl error: window creation failed" << endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable VSync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "opengl error: glad loader init failed" << endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    return window;
}

void imgui_setup(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
	ImGui::GetStyle().FrameBorderSize = 1;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void main_loop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        main_window(window);

        ImGui::Render();
        glViewport(0, 0, 1280, 720);

        glClearColor(0.33f, 0.33f, 0.33f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}

void finalize(GLFWwindow* window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

