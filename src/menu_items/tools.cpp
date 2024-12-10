#include "imgui.h"
#include "tools.h"
#include <iostream>

bool show_metrics = false;
bool show_itemPicker = false;
bool show_stackTool = false;
bool show_demoWindow = false;

void item_tools_metrics() {
	if (show_metrics) ImGui::ShowMetricsWindow(&show_metrics);
}

void item_tools_stackTool() {
	if (show_stackTool) ImGui::ShowIDStackToolWindow(&show_stackTool);
}

void item_tools_demoWindow() {
	if (show_demoWindow) ImGui::ShowDemoWindow(&show_demoWindow);
}

