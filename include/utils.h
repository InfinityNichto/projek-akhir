#ifndef UTILS_H
#define UTILS_H

#include "vars.h"

#include "imgui.h"
#include <string>
#include <sstream>
#include <random>
#include <limits>

// forward declaration from vars.h to vars.cpp
extern std::mt19937 rng;

struct scrolling_text {
private:
	std::string original;
	std::string display;
	size_t limit;
	float step;
	size_t size;

public:
	scrolling_text(std::string text, size_t limit);
	void scroll(float inc);
	void reset();
	std::string str() const;
	const char* cstr() const;
};

void hyperlink(const char* desc, const char* url);
void text_centered(const char* text, int type);
void help_marker(const char* desc);
void open_url(const char* url);
void cycle_rainbow(ImVec4* color, size_t* cycle_ptr, float inc);
const char* ImVec2_to_cstr(const ImVec2& vec);
const char* ImVec4_to_cstr(const ImVec4& vec);
void draw_grid(size_t count, float thickness);

template <typename T> inline T next_int() {
	std::uniform_int_distribution<T> range_dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	T lb = range_dist(rng), ub = range_dist(rng);
	T min = std::min(lb, ub), max = std::max(lb, ub);

	std::uniform_int_distribution<T> dist(min, max);
	return dist(rng);
}

template <typename T> inline T next_int(T min, T max) {
	std::uniform_int_distribution<T> dist(min, max);
	return dist(rng);
}

template <typename T> inline T next_real() {
	std::uniform_real_distribution<T> range_dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	T lb = range_dist(rng), ub = range_dist(rng);
	T min = std::min(lb, ub), max = std::max(lb, ub);

	std::uniform_real_distribution<T> dist(min, max);
	return dist(rng);
}

template <typename T> inline T next_real(T max) {
	std::uniform_real_distribution<T> dist(0, max);
	return dist(rng);
}

template <typename T> inline T next_real(T min, T max) {
	std::uniform_real_distribution<T> dist(min, max);
	return dist(rng);
}

template <typename... Args> inline void log_clipboard(const char* fmt, Args... args) {
	ImGui::LogToClipboard();
	ImGui::LogText(fmt, args...);
	ImGui::LogFinish();
}

template <typename... Args> inline void log_tty(const char* fmt, Args... args) {
	ImGui::LogToTTY();
	ImGui::LogText(fmt, args...);
	ImGui::LogFinish();
}

template <typename... Args> inline void log_file(const char* path, const char* fmt, Args... args) {
	ImGui::LogToFile(0, path);
	ImGui::LogText(fmt, args...);
	ImGui::LogFinish();
}

template <typename... Args> inline std::string build_str(Args... args) {
	std::stringstream ss;
	(ss << ... << args);
	return ss.str();
}

// unsafe, try to use build_str(...).c_str() instead
template <typename... Args> inline const char* build_cstr(Args... args) {
	std::string buf = build_str(args...);
	return buf.c_str();
}

#endif

