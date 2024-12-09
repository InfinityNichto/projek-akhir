#include "imgui.h"
#include "edit.h"

bool show_styleEditor = false;
void item_edit_styleEditor() {
	ImGui::Begin("Style Editor", &show_styleEditor);
    ImGui::ShowStyleEditor();
    ImGui::End();
}

void item_edit_reset() {
}

