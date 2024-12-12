#include "imgui.h"
#include "windows/menu_items/edit.h"

bool show_styleEditor = false;

void item_edit_styleEditor() {
	if (show_styleEditor) {
		ImGui::Begin("Style Editor", &show_styleEditor);
    	ImGui::ShowStyleEditor();
	    ImGui::End();
	}
}

void item_edit_reset() {
}

