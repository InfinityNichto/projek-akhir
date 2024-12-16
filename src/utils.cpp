#include "imgui.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
	#include <windows.h>
#endif

rect::rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
rect::rect(ImVec2 pos, float w, float h) : x(pos.x), y(pos.y), w(w), h(h) {}
rect::rect(float x, float y, ImVec2 size) : x(x), y(y), w(size.x), h(size.y) {}
rect::rect(ImVec2 pos, ImVec2 size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}

rect::rect(const rect& other) = default;
rect& rect::operator=(const rect& other) = default;

ImVec2 rect::pos() const { return ImVec2(x, y); }
ImVec2 rect::size() const { return ImVec2(w, h); }
ImVec2 rect::top_left() const { return ImVec2(x, y); }
ImVec2 rect::top_right() const { return ImVec2(x + w, y); }
ImVec2 rect::bottom_left() const { return ImVec2(x, y + h); }
ImVec2 rect::bottom_right() const { return ImVec2(x + w, y + h); }
ImVec2 rect::mid_left() const { return ImVec2(x, h * 0.5 + y); }
ImVec2 rect::mid_right() const { return ImVec2(x + w, h * 0.5 + y); }
ImVec2 rect::mid_top() const { return ImVec2(w * 0.5 + x, y); }
ImVec2 rect::mid_bottom() const { return ImVec2(w * 0.5 + x, y + h); }
ImVec2 rect::center() const { return ImVec2(w * 0.5 + x, h * 0.5 + y); }

std::string rect::to_string() {
    return build_str("[", x, ", ", y, ", ", w, ", ", h, "]");
}

scrolling_text::scrolling_text(std::string text, size_t limit) : original(text + " ~ "), display(original), limit(limit), step(0) {
    size = original.length();
	while (size < limit) {
      original += original;
      size += size;
    }
}

void scrolling_text::scroll(float inc) {
	size_t floored = std::floor(step);
	size_t gap = size - floored;

	if (gap > limit) display = original.substr(floored, limit);
	else display = original.substr(floored, gap) + original.substr(0, limit - gap);

	float incremented = step + inc;
	step = incremented > size ? incremented - size : incremented;
}

void scrolling_text::reset() {
	display = original;
}

std::string scrolling_text::str() const {
	return display;
}

const char* scrolling_text::cstr() const {
	return display.c_str();
}

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
    float window_width = ImGui::GetWindowSize().x;
    float text_width = ImGui::CalcTextSize(text).x;

    ImGui::SetCursorPosX((window_width - text_width) * 0.5);
    switch (type) {
      case 0:
        ImGui::TextUnformatted(text);
        break;   
      case 1:
        ImGui::TextDisabled("%s", text);
        break;
    }
}

void text_centered_vh(const char* text, int type) {
    rect window_data = get_current_window_data();
    ImVec2 text_size = ImGui::CalcTextSize(text);

    ImGui::SetCursorPos(ImVec2((window_data.w - text_size.x) * 0.5, (window_data.h * 0.5) - text_size.y));
    switch(type) {
      case 0:
        ImGui::TextUnformatted(text);
        break;
      case 1:
        ImGui::TextDisabled("%s", text);
        break;
    }
}

void separator_heading(const char* heading) {
    ImGui::Spacing(); text_centered(heading, 1);
    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
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

std::string ImVec2_to_str(const ImVec2& vec) {
    return build_str("[", vec.x, ", ", vec.y, "]");
}

const char* ImVec2_to_cstr(const ImVec2& vec) {
	return build_cstr("[", vec.x, ", ", vec.y, "]");
}

std::string ImVec4_to_str(const ImVec4& vec) {
    return build_str("[", vec.x, ", ", vec.y, ", ", vec.z, ", ", vec.w, "]");
}

const char* ImVec4_to_cstr(const ImVec4& vec) {
	return build_cstr("[", vec.x, ", ", vec.y, ", ", vec.z, ", ", vec.w, "]");
}

void draw_grid(size_t count, float thickness) {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 window_pos = ImGui::GetWindowPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	ImVec2 step = ImVec2(window_size.x / count, window_size.y / count);

	for (size_t i = 0; i < count; i++) {
		ImVec2 incremented = ImVec2(window_pos.x + step.x * i, window_pos.y + step.y * i);
	
		draw_list->AddLine(
			ImVec2(window_pos.x, incremented.y),
			ImVec2(window_pos.x + window_size.x, incremented.y),
			IM_COL32(88, 88, 88, 176),
			thickness
		);

		draw_list->AddLine(
			ImVec2(incremented.x, window_pos.y),
			ImVec2(incremented.x, window_pos.y + window_size.y),
			IM_COL32(88, 88, 88, 176),
			thickness
		);
	}
}

std::tm as_localtime(std::time_t time) {
    return *std::localtime(&time);
}

std::string format_time(std::tm localtime, const char* fmt) {
    return build_str(std::put_time(&localtime, fmt));
}

