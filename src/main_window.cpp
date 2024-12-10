#include <GLFW/glfw3.h>
#include "imgui.h"

#include "main_window.h"
#include "utils.h"
#include "menu_items/file.h"
#include "menu_items/edit.h"
#include "menu_items/tools.h"
#include "menu_items/help.h"

void main_window(GLFWwindow* window) {
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 window_size = io.DisplaySize;

	ImGui::SetNextWindowSize(window_size); // fullscreen
	ImGui::SetNextWindowPos(ImVec2(0, 0)); // from 0, 0
	ImGui::SetNextWindowBgAlpha(1); // no transparency

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
							 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus;

	if (ImGui::Begin("Item browser", NULL, flags)) {
		menu_bar(window);

		item_edit_styleEditor();
		item_tools_metrics();
		item_tools_stackTool();
		item_tools_demoWindow();
		item_help_resources(&show_imguiResources);
		item_help_about(&show_aboutWindow);

		tab_bar();

		ImGui::End();
	}
}

void menu_bar(GLFWwindow* window) {
	if (!ImGui::BeginMenuBar()) return;

	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Exit")) item_file_exit(window);
		ImGui::SetItemTooltip("Exit the program");

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Edit")) {
		if (ImGui::MenuItem("Style Editor", NULL, show_styleEditor)) show_styleEditor = !show_styleEditor;
		ImGui::SetItemTooltip("Edit current layout styling");

		ImGui::BeginDisabled();
			if (ImGui::MenuItem("Reset")) item_edit_reset();
			ImGui::SetItemTooltip("Reset layout styling"); ImGui::SameLine(); help_marker("Unimplemented");
		ImGui::EndDisabled();

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Tools")) {

		if (ImGui::MenuItem("Metrics/Debugger", NULL, show_metrics)) show_metrics = !show_metrics;
		ImGui::SetItemTooltip("Show utility window for metrics and debugging");

		if (ImGui::MenuItem("ID stack tool", NULL, show_stackTool)) show_stackTool = !show_stackTool;
		ImGui::SetItemTooltip("Show utility window for inspecting element ID stack");

		if (ImGui::MenuItem("Demo window", NULL, show_demoWindow)) show_demoWindow = !show_demoWindow;
		ImGui::SetItemTooltip("Show the demo window");

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Help")) {
		ImGui::BeginDisabled();
			if (ImGui::MenuItem("Guide")) item_help_guide();
			ImGui::SetItemTooltip("Open the guide document"); ImGui::SameLine(); help_marker("Unimplemented");
		ImGui::EndDisabled();

		if (ImGui::MenuItem("Resources")) show_imguiResources = !show_imguiResources;
		ImGui::SetItemTooltip("Open useful resources for ImGui development");

		if (ImGui::MenuItem("About")) show_aboutWindow = !show_aboutWindow;
		ImGui::SetItemTooltip("About this program");

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();
}

void tab_bar() {
}
