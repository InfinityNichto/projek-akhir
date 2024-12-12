#include "program.h"
#include "vars.h"
#include <iostream>

int main() {
	opengl_setup();
    if (!glfw_window) {
		std::cerr << "opengl setup failed" << std::endl;
        return -1;
    }

	imgui_setup();
    main_loop();
    finalize();
}

