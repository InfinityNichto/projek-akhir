#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

#ifndef IMGUI_CDECL
#ifdef _MSC_VER
#define IMGUI_CDECL __cdecl
#else
#define IMGUI_CDECL
#endif
#endif

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
    ImGuiID ID;

	string name;
	string category;
	float buyPrice;
	float sellPrice;
	int stock;

	Item(string name, string category, float buyPrice, float sellPrice, int stock)
		: name(name), category(category), buyPrice(buyPrice), sellPrice(sellPrice), stock(stock) {};

    static const ImGuiTableSortSpecs* currentSortSpecs;
    
    static void sortWithSortSpecs(ImGuiTableSortSpecs* sortSpecs, Item* items, size_t itemsCount) {
        currentSortSpecs = sortSpecs;
        if (itemsCount > 1) qsort(items, itemsCount, sizeof(items[0]), Item::compareWithSortSpecs);
        currentSortSpecs = NULL;
    }

    static int IMGUI_CDECL compareWithSortSpecs(const void* lhs, const void* rhs) {
        const Item* a = (const Item*)lhs;
        const Item* b = (const Item*)rhs;

        for (int i = 0; i < currentSortSpecs->SpecsCount; i++) {
            const ImGuiTableColumnSortSpecs* sortSpec = &currentSortSpecs->Specs[i];
            int delta = 0;

            if (sortSpec->ColumnIndex == 0) {
                delta = (int)a->ID - (int)b->ID;
            }

            if (delta > 0) {
                return (sortSpec->SortDirection == ImGuiSortDirection_Ascending) ? 1 : -1;
            } else if (delta < 0) {
                return (sortSpec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : 1;
            }
        }

        return (int)a->ID - (int)b->ID;
    }
};

class Hashed {
protected:
	size_t hash;

	size_t computeHash(void* seed) const {
		return std::hash<const void*>{}(seed);
	}

public:
	Hashed() : hash(0) {}
    virtual ~Hashed() {}

    void initHash(void* thisPtr) {
        if (hash == 0) hash = computeHash(thisPtr);
    }

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

class ItemsBrowser : public WindowLayout {
private:
    string _name;

    bool showCategoryIndicator = true;
    bool allowSorting = true;
    bool allowDragUnselected = false;

public:
	ItemsBrowser(string name, float width, float height) : _name(name), WindowLayout(name, width, height) {
        initHash(this);
    }

	void draw() override {
		WindowLayout::draw();
		ImGui::Begin(name.c_str());

        

	    ImGui::End();
	}

	void update() override {
		int fps = ImGui::GetIO().Framerate;
		name = build_str(_name, " | ", fps, " FPS###", hash);
	}
};

// OpenGL error handler
void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
	cerr << "opengl error: " << message << endl;
}

float clearColor[3] = {1, 0, 0};
float cycleInc = 0.005;
int cyclePtr = 0;

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

	ItemsBrowser ib("Items Browser", 600, 400);

	// main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ib.draw();
		ImGui::ShowDemoWindow();

	    ImGui::Render();
        glViewport(0, 0, 1280, 720);

        const int nxPtr = (cyclePtr + 1) % 3;
        if (clearColor[nxPtr] < 1) clearColor[nxPtr] += cycleInc;
        else if (clearColor[cyclePtr] > 0) clearColor[cyclePtr] -= cycleInc;
        else cyclePtr = nxPtr;

        glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.00f);
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

