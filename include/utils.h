#ifndef UTILS_H
#define UTILS_H

#include "imgui.h"
#include <string>
#include <sstream>

void hyperlink(const char* desc, const char* url);
void text_centered(const char* text, int type);
void help_marker(const char* desc);
void open_url(const char* url);
void cycle_rainbow(ImVec4* color, size_t* cycle_ptr, float inc);

template <typename... Args>
void log_clipboard(const char* fmt, Args... args) {
	ImGui::LogToClipboard();
	ImGui::LogText(fmt, args...);
	ImGui::LogFinish();
}

template <typename... Args>
void log_tty(const char* fmt, Args... args) {
	ImGui::LogToTTY();
	ImGui::LogText(fmt, args...);
	ImGui::LogFinish();
}

template <typename... Args>
void log_file(const char* path, const char* fmt, Args... args) {
	ImGui::LogToFile(0, path);
	ImGui::LogText(fmt, args...);
	ImGui::LogFinish();
}

template <typename... Args>
std::string build_str(Args... args) {
	std::stringstream ss;
	(ss << ... << args);
	return ss.str();
}

template <typename... Args>
const char* build_cstr(Args... args) {
	static string str = buildStr(args...);
	return str.c_str();
}

#endif

