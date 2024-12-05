#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

using namespace std;

template <typename... Args>
string build_str(Args... args) {
	stringstream ss;
	(ss << ... << args);
	return ss.str();
}

template <typename... Args>
const char* build_c_str(Args... args) {
	static string str = build_str(args...);
	return str.c_str();
}

struct Item {
public:
	string name;
	string category;
	float buyPrice;
	float sellPrice;
	int stock;

	Item(string name, string category, float buyPrice, float sellPrice, int qty)
		: name(name), category(category), buyPrice(buyPrice), sellPrice(sellPrice), stock(stock) {};
};

class Hashed {
protected:
	size_t hash;

	size_t computeHash() const {
		return std::hash<const void*>{}(static_cast<const void*>(this));
	}

public:
	Hashed() : hash(computeHash()) {}
	virtual ~Hashed() {}

	size_t getHashCode() const {
		return hash;
	}
};

class WindowLayout : public Hashed {
protected:
	string name;
	float width;
	float height;

public:
	WindowLayout(string name, float width, float height) : name(name), width(width), height(height) {}
	virtual ~WindowLayout() {}

	virtual void draw() {
		update();
		ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once);
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_Once);
	}

	virtual void update() {};
};

class MainWindow : public WindowLayout {
private:
	vector<Item> items;
	size_t itemsCount = 0;
	string _name;

	char tmp_newItem_name[128] = "";
	char tmp_newItem_category[128] = "";
	float tmp_newItem_buyPrice = 0;
	float tmp_newItem_sellPrice = 0;
	int tmp_newItem_stock = 0;

	void drawItemTable() {
    	ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    	if (ImGui::BeginTable("itemsTable", 6, flags)) {
	        ImGui::TableSetupColumn("No.");
    	    ImGui::TableSetupColumn("Name");
    		ImGui::TableSetupColumn("Category");
        	ImGui::TableSetupColumn("Buy price");
	        ImGui::TableSetupColumn("Sell price");
    	    ImGui::TableSetupColumn("Stock");
        	ImGui::TableHeadersRow();

	        for (int i = 0; i < itemsCount; i++) {
    	        ImGui::TableNextRow();
        	    ImGui::TableNextColumn(); ImGui::Text("%d", i + 1);
            	ImGui::TableNextColumn(); ImGui::Text("%s", items[i].name.c_str());
	            ImGui::TableNextColumn(); ImGui::Text("%s", items[i].category.c_str());
    	        ImGui::TableNextColumn(); ImGui::Text("Rp. %d", items[i].buyPrice);
        	    ImGui::TableNextColumn(); ImGui::Text("Rp. %d", items[i].sellPrice);
            	ImGui::TableNextColumn(); ImGui::Text("%d", items[i].stock);
	        }

    	    ImGui::EndTable();
    	}
	}

	void drawNewItemForm() {
		ImGui::Text("Name: ");
		ImGui::InputText("##inputName", tmp_newItem_name, IM_ARRAYSIZE(tmp_newItem_name));

		ImGui::Text("Category: ");
		ImGui::InputText("##inputCategory", tmp_newItem_category, IM_ARRAYSIZE(tmp_newItem_category));

		ImGui::Text("Buy price: ");
		ImGui::InputFloat("##inputBuyPrice", &tmp_newItem_buyPrice);

		ImGui::Text("Sell price: ");
		ImGui::InputFloat("##inputSellPrice", &tmp_newItem_sellPrice);

		ImGui::Text("Stock: ");
		ImGui::InputInt("##inputStock", &tmp_newItem_stock);
	}

public:
	MainWindow(string name, float width, float height) : _name(name), WindowLayout(name, width, height) {}

	void draw() override {
		WindowLayout::draw();
		ImGui::Begin(name.c_str());

		drawItemTable();

		ImGui::Text("-- Add new item below --");
		drawNewItemForm();

		if (ImGui::Button("Submit")) {
			items.push_back(Item(tmp_newItem_name, tmp_newItem_category, tmp_newItem_buyPrice, tmp_newItem_sellPrice, tmp_newItem_stock));
			itemsCount++;
		}

		ImGui::End();
	}

	void update() override {
		int fps = ImGui::GetIO().Framerate;
		name = build_str(_name, " | ", fps, " FPS###", hash);
	}
};

// OpenGL error handler
void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
							  GLsizei length, const GLchar *message, const void *userParam) {
	cerr << "opengl error: " << message << endl;
}

int main(int, char**) {
	// opengl setup
	if (!glfwInit()) {
		cerr << "opengl error: glfwInit failed" << endl;
		return -1;
	}

	GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui - Powered by OpenGL3 + GLFW 3.4", NULL, NULL);
	if (!window) {
		glfwTerminate();
		cerr << "opengl error: window creation failed" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // vsync	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "opengl error: loader init failed" << endl;
		return -1;
	}

	// imgui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	MainWindow mw("Items", 600, 400);

	// main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		mw.draw();
		ImGui::ShowDemoWindow();

	    ImGui::Render();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
	}

	// cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

