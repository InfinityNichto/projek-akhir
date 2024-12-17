#include <GLFW/glfw3.h>
#include "imgui.h"

#include "vars.h"
#include "utils.h"
#include "windows/menu_bar_window.h"
#include "windows/menu_items/file.h"
#include "windows/menu_items/edit.h"
#include "windows/menu_items/tools.h"
#include "windows/menu_items/help.h"

void menu_bar_window() {
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(display_size().x, 46));
	ImGui::SetNextWindowBgAlpha(1);

	ImGuiWindowFlags window_flags = common_window_flags | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

	if (ImGui::Begin("##menu_bar", NULL, window_flags)) {
		menu_bar();

		item_edit_styleEditor();
		item_tools_metrics();
		item_tools_stackTool();
		item_tools_demoWindow();
		item_help_resources(&show_imguiResources);
		item_help_about(&show_aboutWindow);

		tab_bar();

		update_prev_window_data();
		ImGui::End();
	}
}

void menu_bar() {
	if (!ImGui::BeginMenuBar()) return;

	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Exit")) item_file_exit();
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
	if (!ImGui::BeginTabBar("##tab_bar")) return;

	if (ImGui::BeginTabItem("Workspace")) {
        workspace_open = true;
		log_open = false;

        ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Logs")) {
        log_open = true;

		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();
}

