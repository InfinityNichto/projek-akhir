#ifndef UTILS_H
#define UTILS_H

#include "imgui.h"

void hyperlink(const char* desc, const char* url);
void text_centered(const char* text, int type);
void help_marker(const char* desc);
void open_url(const char* url);
void cycle_rainbow(ImVec4* color, size_t* cycle_ptr, float inc);

#endif

