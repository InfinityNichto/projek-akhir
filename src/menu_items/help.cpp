#include "imgui.h"
#include "../utils.h"
#include "help.h"

bool show_imguiResources = false;
bool show_aboutWindow = false;

ImVec4 rgb = {1, 0, 0, 1};
size_t rgb_cycle_ptr = 0;

void item_help_guide() {}

void item_help_resources(bool* show) {
	if (!(*show)) return;

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.84f, 0.00f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12f, 0.12f, 0.12f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.00f, 0.00f, 0.00f, 0.54f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.31f, 0.00f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.13f, 0.13f, 0.13f, 0.50f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.13f, 0.13f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.14f, 0.00f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.42f, 0.42f, 0.42f, 0.31f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.31f, 0.00f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.17f, 0.00f, 0.55f, 1.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.00f, 2.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.00f, 3.00f));
    ImGui::SetNextWindowSize(ImVec2(500,600), ImGuiCond_Once);

	if (ImGui::Begin("Resources", show, ImGuiWindowFlags_NoCollapse)) {
    	ImGui::TextWrapped("Some useful resources for developers using Dear ImGui.");
	    ImGui::TextWrapped("Keep in mind that the most helpful resource will always be the Dear ImGui Demo (Tools > Demo Window) and imgui/imgui_demo.cpp.");
    	ImGui::Spacing();
	    ImGui::TextWrapped("Click = Copy to clipboard");
    	ImGui::Spacing();

	    ImGui::CollapsingHeader("Dear ImGui", ImGuiTreeNodeFlags_DefaultOpen); {
	        ImGui::Bullet();
    	    if (ImGui::SmallButton("Dear ImGui Source: github.com/ocornut/imgui")) {
        	    ImGui::LogToClipboard();
	            ImGui::LogText("https://github.com/ocornut/imgui");
    	        ImGui::LogFinish();
        	}

	        ImGui::Bullet();
    	    if (ImGui::SmallButton("Issues")) {
        	    ImGui::LogToClipboard();
	            ImGui::LogText("https://github.com/ocornut/imgui/issues");
    	        ImGui::LogFinish();
        	}

	        ImGui::Bullet();
    	    if (ImGui::SmallButton("Wiki")) {
        	    ImGui::LogToClipboard();
            	ImGui::LogText("https://github.com/ocornut/imgui/wiki");
	            ImGui::LogFinish();
    	    }

        	ImGui::Bullet();
	        if (ImGui::SmallButton("Manual")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://pthom.github.io/imgui_manual_online");
            	ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("discourse.dearimgui.org")) {
	            ImGui::LogToClipboard();
    	        ImGui::LogText("https://discourse.dearimgui.org/");
        	    ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("Discussions")) {
	            ImGui::LogToClipboard();
    	        ImGui::LogText("https://github.com/ocornut/imgui/discussions");
        	    ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
	        if (ImGui::SmallButton("How to open an Issue or Pull Request #2261")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/ocornut/imgui/issues/2261");
	            ImGui::LogFinish();
    	    }

        	ImGui::Bullet();
	        if (ImGui::SmallButton("Docking")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/ocornut/imgui/wiki/Docking");
	            ImGui::LogFinish();
    	    }

        	ImGui::Bullet();
	        if (ImGui::SmallButton("Gallery")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/ocornut/imgui/issues/4451");
            	ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("Software using DearImGui")) {
	            ImGui::LogToClipboard();
    	        ImGui::LogText("https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui");
        	    ImGui::LogFinish();
	        }
    	}

	    ImGui::Spacing();
		cycle_rainbow(&rgb, &rgb_cycle_ptr, 0.05);
    	ImGui::PushStyleColor(ImGuiCol_Header, rgb);
	    
		ImGui::CollapsingHeader("Cool Addons", ImGuiTreeNodeFlags_DefaultOpen); {
        	ImGui::Bullet();
	        if (ImGui::SmallButton("HankiDesign/awesome-dear-imgui")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/HankiDesign/awesome-dear-imgui");
            	ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("issues/useful widgets")) {
            	ImGui::LogToClipboard();
    	        ImGui::LogText("https://github.com/ocornut/imgui/issues?q=label%%3A\"useful+widgets\"");
	            ImGui::LogFinish();
        	}

	        ImGui::Bullet();
    	    if (ImGui::SmallButton("epezent/implot")) {
        	    ImGui::LogToClipboard();
            	ImGui::LogText("https://github.com/epezent/implot");
	            ImGui::LogFinish();
    	    }

        	ImGui::Bullet();
	        if (ImGui::SmallButton("soufianekhiat/DearWidgets")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/soufianekhiat/DearWidgets");
            	ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("dfranx/ImFileDialog")) {
            	ImGui::LogToClipboard();
	            ImGui::LogText("https://github.com/dfranx/ImFileDialog");
    	        ImGui::LogFinish();
        	}

        	ImGui::Bullet();
	        if (ImGui::SmallButton("Toggle Button")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/ocornut/imgui/issues/1537#issuecomment-355569554");
            	ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("Knob")) {
            	ImGui::LogToClipboard();
	            ImGui::LogText("https://github.com/ocornut/imgui/issues/942#issuecomment-268369298");
    	        ImGui::LogFinish();
        	}

	        ImGui::Bullet();
    	    if (ImGui::SmallButton("Nelarius/imnodes")) {
        	    ImGui::LogToClipboard();
            	ImGui::LogText("https://github.com/Nelarius/imnodes");
	            ImGui::LogFinish();
    	    }

        	ImGui::Bullet();
    	    if (ImGui::SmallButton("thedmd/imgui-node-editor")) {
	            ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/thedmd/imgui-node-editor");
            	ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("aiekick/ImGuiFontStudio")) {
            	ImGui::LogToClipboard();
	            ImGui::LogText("https://github.com/aiekick/ImGuiFontStudio");
    	        ImGui::LogFinish();
        	}

	        ImGui::Bullet();
    	    if (ImGui::SmallButton("Add extra keys #2625")) {
        	    ImGui::LogToClipboard();
            	ImGui::LogText("https://github.com/ocornut/imgui/pull/2625");
	            ImGui::LogFinish();
    	    }
	    }

    	ImGui::PopStyleColor(1);
	    ImGui::Spacing();
    	
		ImGui::CollapsingHeader("Frameworks", ImGuiTreeNodeFlags_DefaultOpen); {
        	ImGui::Bullet();
	        if (ImGui::SmallButton("pthom/hello_imgui")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/pthom/hello_imgui");
            	ImGui::LogFinish();
	        }

    	    ImGui::Bullet();
        	if (ImGui::SmallButton("JamesBoer/ImFrame")) {
            	ImGui::LogToClipboard();
	            ImGui::LogText("https://github.com/JamesBoer/ImFrame");
    	        ImGui::LogFinish();
        	}

	        ImGui::Bullet();
    	    if (ImGui::SmallButton("pr0g/sdl-bgfx-imgui-starter")) {
        	    ImGui::LogToClipboard();
            	ImGui::LogText("https://github.com/pr0g/sdl-bgfx-imgui-starter");
	            ImGui::LogFinish();
    	    }

        	ImGui::Bullet();
	        if (ImGui::SmallButton("mahilab/mahi-gui")) {
    	        ImGui::LogToClipboard();
        	    ImGui::LogText("https://github.com/mahilab/mahi-gui");
            	ImGui::LogFinish();
	        }
    	}

		ImGui::PopStyleColor(10);
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
        text_centered("projek-akhir", 0);
        ImGui::Separator();
        ImGui::Text("Version: 3b2153b");
        ImGui::Text("Source: InfinityNichto/projek-akhir");
        ImGui::Text("ImGui: v1.91.5");
        ImGui::Separator();

        if (ImGui::Button("Back")) {
			ImGui::CloseCurrentPopup();
			*show = false;
		}

        ImGui::EndPopup();
    }
}

