#include "imgui.h"
#include "utils.h"
#include "windows/menu_items/help.h"

bool show_imguiResources = false;
bool show_aboutWindow = false;

ImVec4 rgb = {1, 0, 0, 1};
size_t rgb_cycle_ptr = 0;
float rgb_cycle_inc = 0.01;

void item_help_guide() {}

void item_help_resources(bool* show) {
	if (!(*show)) return;

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.00f, 2.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.00f, 3.00f));
    ImGui::SetNextWindowSize(ImVec2(500,600), ImGuiCond_Once);

	if (ImGui::Begin("Resources", show, ImGuiWindowFlags_NoCollapse)) {
		ImGui::TextWrapped("Some useful resources for developers using Dear ImGui.");
	    ImGui::TextWrapped("Keep in mind that the most helpful resource will always be the Dear ImGui Demo (Tools > Demo Window) and imgui/imgui_demo.cpp.");
    	ImGui::Spacing();

		if (ImGui::CollapsingHeader("Dear ImGui", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Bullet();
			hyperlink("Dear ImGui Source: github.com/ocornut/imgui", "https://github.com/ocornut/imgui");
			
			ImGui::Bullet();
	    	hyperlink("Issues", "https://github.com/ocornut/imgui/issues");

			ImGui::Bullet();
			hyperlink("Wiki", "https://github.com/ocornut/imgui/wiki");

			ImGui::Bullet();
			hyperlink("Manual", "https://pthom.github.io/imgui_manual_online");

	   		ImGui::Bullet();
			hyperlink("discourse.dearimgui.org", "https://discourse.dearimgui.org/");

    		ImGui::Bullet();
    		hyperlink("Discussions", "https://github.com/ocornut/imgui/discussions");

    		ImGui::Bullet();
    		hyperlink("How to open an Issue or Pull Request #2261", "https://github.com/ocornut/imgui/issues/2261");

    		ImGui::Bullet();
    		hyperlink("Docking", "https://github.com/ocornut/imgui/wiki/Docking");

    		ImGui::Bullet();
    		hyperlink("Gallery", "https://github.com/ocornut/imgui/issues/4451");

    		ImGui::Bullet();
    		hyperlink("Software using DearImGui", "https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui");
		}

    	ImGui::Spacing();
    	
		if (ImGui::CollapsingHeader("Cool Addons", ImGuiTreeNodeFlags_DefaultOpen)) {
        	ImGui::Bullet();
        	hyperlink("HankiDesign/awesome-dear-imgui", "https://github.com/HankiDesign/awesome-dear-imgui");

        	ImGui::Bullet();
        	hyperlink("issues/useful widgets", "https://github.com/ocornut/imgui/issues?q=label%%3A\"useful+widgets\"");

        	ImGui::Bullet();
        	hyperlink("epezent/implot", "https://github.com/epezent/implot");

        	ImGui::Bullet();
        	hyperlink("soufianekhiat/DearWidgets", "https://github.com/soufianekhiat/DearWidgets");

        	ImGui::Bullet();
        	hyperlink("dfranx/ImFileDialog", "https://github.com/dfranx/ImFileDialog");

        	ImGui::Bullet();
        	hyperlink("Toggle Button", "https://github.com/ocornut/imgui/issues/1537#issuecomment-355569554");

        	ImGui::Bullet();
        	hyperlink("Knob", "https://github.com/ocornut/imgui/issues/942#issuecomment-268369298");

        	ImGui::Bullet();
        	hyperlink("Nelarius/imnodes", "https://github.com/Nelarius/imnodes");

        	ImGui::Bullet();
        	hyperlink("thedmd/imgui-node-editor", "https://github.com/thedmd/imgui-node-editor");

        	ImGui::Bullet();
        	hyperlink("aiekick/ImGuiFontStudio", "https://github.com/aiekick/ImGuiFontStudio");

        	ImGui::Bullet();
    	    hyperlink("Add extra keys #2625", "https://github.com/ocornut/imgui/pull/2625");
		}
    	
		ImGui::Spacing();

    	if (ImGui::CollapsingHeader("Frameworks", ImGuiTreeNodeFlags_DefaultOpen)) {
        	ImGui::Bullet();
        	hyperlink("pthom/hello_imgui", "https://github.com/pthom/hello_imgui");

        	ImGui::Bullet();
        	hyperlink("JamesBoer/ImFrame", "https://github.com/JamesBoer/ImFrame");

        	ImGui::Bullet();
        	hyperlink("pr0g/sdl-bgfx-imgui-starter", "https://github.com/pr0g/sdl-bgfx-imgui-starter");

        	ImGui::Bullet();
        	hyperlink("mahilab/mahi-gui", "https://github.com/mahilab/mahi-gui");
		}

		ImGui::PopStyleVar(2);
	    ImGui::End();
	}
}

void item_help_about(bool* show) {
	if (!(*show)) return;

	ImGui::OpenPopup("About");
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5, 0.5));
    
	if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        text_centered("V-ME", 0);
        ImGui::Separator();
        ImGui::Text("Version: 9b60a1f");
        ImGui::Text("Source:"); ImGui::SameLine(); hyperlink("InfinityNichto/projek-akhir", "https://github.com/InfinityNichto/projek-akhir");
        ImGui::Text("ImGui: v1.91.5");
        ImGui::Separator();

        if (ImGui::Button("Back")) {
			ImGui::CloseCurrentPopup();
			*show = false;
		}

        ImGui::EndPopup();
    }
}

