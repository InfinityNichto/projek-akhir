#include "program.h"
#include <iostream>

int main() {
	GLFWwindow* window = opengl_setup();
    if (!window) {
		std::cerr << "opengl setup failed" << std::endl;
        return -1;
    }

    imgui_setup(window);
    main_loop(window);
    finalize(window);
}

