#include "imgui.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <string>

#ifdef _WIN32
	#include <windows.h>
#endif

void hyperlink(const char* desc, const char* url) {
	ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "%s", desc);

	if (ImGui::IsItemHovered()) {
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		ImGui::SetTooltip("%s", url);
		if (ImGui::IsMouseClicked(0)) open_url(url);
	}

	ImGui::SetItemTooltip("%s", url); ImGui::SameLine(); help_marker("If your OS is neither Windows, Linux, or MacOS, the URL will be copied to your clipboard instead");
}

void text_centered(const char* text, int type) {
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth   = ImGui::CalcTextSize(text).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5);
    switch (type) {
      case 0:
        ImGui::TextUnformatted(text);
        break;
    
      case 1:
        ImGui::TextDisabled("%s", text);
        break;
    }
}

void help_marker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void open_url(const char* url) {
#ifdef _WIN32
	ShellExecute(0, "open", url, 0, 0, SW_SHOWNORMAL);
#elif __linux__
	system(("xdg-open " + std::string(url)).c_str());
#elif __APPLE__
	system(("open " + std::string(url)).c_str());
#else
	ImGui::LogToClipboard();
	ImGui::LogText(url);
    ImGui::LogFinish();
#endif
}

void cycle_rainbow(ImVec4* color, size_t* cycle_ptr, float inc) {
    size_t nx_ptr = (*cycle_ptr + 1) % 3;

    float* components[3] = { &color->x, &color->y, &color->z};
    float& current = *components[*cycle_ptr];
	float& nx = *components[nx_ptr];

    if (*cycle_ptr == 3) *cycle_ptr = 0;

    if (nx <= 1) nx += inc;
    else if (current >= 0) current -= inc;
    else *cycle_ptr = nx_ptr;
}

const char*ImVec2_to_cstr(const ImVec2& vec) {
	return build_cstr("[", vec.x, ", ", vec.y, "]");
}

const char* ImVec4_to_cstr(const ImVec4& vec) {
	return build_cstr("[", vec.x, ", ", vec.y, ", ", vec.z, ", ", vec.w, "]");
}

