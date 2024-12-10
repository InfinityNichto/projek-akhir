#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h>

#include "program.h"
#include "utils.h"
#include "menu_items/file.h"
#include "menu_items/edit.h"
#include "menu_items/tools.h"
#include "menu_items/help.h"

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
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void main_loop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        inner_main_loop(window);

        ImGui::Render();
        glViewport(0, 0, 1280, 720);

        glClearColor(0.33f, 0.33f, 0.33f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}

void inner_main_loop(GLFWwindow* window) {
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 window_size = io.DisplaySize;

	ImGui::SetNextWindowSize(window_size); // fullscreen
	ImGui::SetNextWindowPos(ImVec2(0, 0)); // from 0, 0
	ImGui::SetNextWindowBgAlpha(1); // no transparency

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
							 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus;

	if (ImGui::Begin("Item browser", nullptr, flags)) {
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Exit")) {
					item_file_exit(window);
				}
				ImGui::SetItemTooltip("Exit the program");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Style Editor", NULL, show_styleEditor)) {
					show_styleEditor = !show_styleEditor;
				}
				ImGui::SetItemTooltip("Edit current layout styling");
				
				ImGui::BeginDisabled();

				if (ImGui::MenuItem("Reset")) {
					item_edit_reset();
				}

				ImGui::EndDisabled();

				ImGui::SetItemTooltip("Reset layout styling"); ImGui::SameLine(); help_marker("Unimplemented");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools")) {
				
				if (ImGui::MenuItem("Metrics/Debugger", NULL, show_metrics)) {
					show_metrics = !show_metrics;
				}

				ImGui::SetItemTooltip("Show utility window for metrics and debugging");

				if (ImGui::MenuItem("ID stack tool", NULL, show_stackTool)) {
					show_stackTool = !show_stackTool;
				}

				ImGui::SetItemTooltip("Show utility window for inspecting element ID stack");
				
				if (ImGui::MenuItem("Demo window", NULL, show_demoWindow)) {
					show_demoWindow = !show_demoWindow;
				}

				ImGui::SetItemTooltip("Show the demo window");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help")) {
				ImGui::BeginDisabled();

				if (ImGui::MenuItem("Guide")) {
					item_help_guide();
				}
	
				ImGui::EndDisabled();

				ImGui::SetItemTooltip("Open the guide document"); ImGui::SameLine(); help_marker("Unimplemented");

				if (ImGui::MenuItem("Resources")) {
					show_imguiResources = !show_imguiResources;
				}

				ImGui::SetItemTooltip("Open useful resources for ImGui development");

				if (ImGui::MenuItem("About")) {
					show_aboutWindow = !show_aboutWindow;
				}

				ImGui::SetItemTooltip("About this program");

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		item_edit_styleEditor();
		item_tools_metrics();
		item_tools_stackTool();
		item_tools_demoWindow();
		item_help_resources(&show_imguiResources);
		item_help_about(&show_aboutWindow);

		ImGui::Text("Fullscreen, non-resizable");
	}

	ImGui::End();
}

void finalize(GLFWwindow* window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

