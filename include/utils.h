#ifndef UTILS_H
#define UTILS_H

#include "vars.h"

#include "imgui.h"
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <limits>
#include <chrono>

// forward declaration from vars.h to vars.cpp
extern std::mt19937 rng;

struct rect {
    float x;
    float y;
    float w;
    float h;

    rect(float x, float y, float w, float h);
    rect(ImVec2 pos, float w, float h);
    rect(float x, float y, ImVec2 size);
    rect(ImVec2 pos, ImVec2 size);

    rect(const rect& other);
    rect& operator=(const rect& other);

    ImVec2 pos() const;
    ImVec2 size() const;
    ImVec2 top_left() const;
    ImVec2 top_right() const;
    ImVec2 bottom_left() const;
    ImVec2 bottom_right() const;
    ImVec2 mid_left() const;
    ImVec2 mid_right() const;
    ImVec2 mid_top() const;
    ImVec2 mid_bottom() const;
    ImVec2 center() const;

    std::string to_string();
};

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
void text_centered_vh(const char* text, int type);
void separator_heading(const char* heading);
void help_marker(const char* desc);
void open_url(const char* url);
void cycle_rainbow(ImVec4* color, size_t* cycle_ptr, float inc);
std::string ImVec2_to_str(const ImVec2& vec);
const char* ImVec2_to_cstr(const ImVec2& vec);
std::string ImVec2_to_str(const ImVec4& vec);
const char* ImVec4_to_cstr(const ImVec4& vec);
void draw_grid(size_t count, float thickness);
void separator_heading(const char* heading);
std::tm as_localtime(time_t time);
std::string format_time(std::tm localtime, const char* fmt);

template <typename... Args> inline void text_hover_formatted(const char* fmt, Args... args) {
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip(fmt, args...);
	}
}

template <typename... Args> inline void text_centered_formatted(const char* fmt, Args... args) {
	size_t buf_len = std::snprintf(nullptr, 0, fmt, args...) + 1;
	std::vector<char> buf(buf_len);
	std::snprintf(buf.data(), buf_len, fmt, args...);
	const char* text = buf.data();

	float window_width = ImGui::GetWindowSize().x;
    float text_width = ImGui::CalcTextSize(text).x;

    ImGui::SetCursorPosX((window_width - text_width) * 0.5);
    ImGui::Text("%s", text);
}

template <typename... Args> inline void text_wrapped(const char* fmt, Args... args) {
	ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + ImGui::GetContentRegionAvail().x);
	ImGui::TextWrapped(fmt, args...);
	ImGui::PopTextWrapPos();
}

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

// unsafe and buggy, try to use build_str(...).c_str() instead
template <typename... Args> inline const char* build_cstr(Args... args) {
	std::string buf = build_str(args...);
	return buf.c_str();
}

#endif

