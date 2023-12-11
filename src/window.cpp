// OLD CODE - DO NOT TOUCH THIS GARBAGE!
#include "window.h"

static struct GLFW_Init_Struct_T {
	GLFW_Init_Struct_T() {
		glfwInit();
	}
	~GLFW_Init_Struct_T() {
		glfwTerminate();
	}
} GLFW_Init;

void Window::open(const char* Title, uint32_t X, uint32_t Y, bool fullscreen) {
	_width = X;
	_height = Y;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (fullscreen) {
		_width = mode->width;
		_height = mode->height;
	}

	// To prevent crazzily weird FPS
	glfwSwapInterval(1);

	_handle = glfwCreateWindow(_width, _height, Title, fullscreen ? monitor : nullptr, nullptr);
	glfwMakeContextCurrent(_handle);
}

void Window::close(void) {
	glfwDestroyWindow(_handle);
}

bool Window::should_close(void) {
	return glfwWindowShouldClose(_handle);
}

void Window::update_screen(void) {
	glfwSwapBuffers(_handle);
}

void Window::update_poll_events(void) {
	glfwPollEvents();
}

void Window::set_input_callback(GLFWcursorposfun MouseCallback) {
	glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(_handle, MouseCallback);
}

bool Window::get_key(uint32_t KeyCode) {
	return glfwGetKey(_handle, KeyCode);
}

void Window::set_visibility(bool vis) {
	if (vis) {
		glfwShowWindow(_handle);
	}
	else {
		glfwHideWindow(_handle);
	}
}