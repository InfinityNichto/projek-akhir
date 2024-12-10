#include "imgui.h"
#include "utils.h"

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
