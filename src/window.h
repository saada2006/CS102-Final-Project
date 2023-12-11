// OLD CODE - DO NOT TOUCH THIS GARBAGE!
#ifndef OPENGL_LIGHT_TRANSPORT_WINDOW_H
#define OPENGL_LIGHT_TRANSPORT_WINDOW_H

#include "opengl.h"
#include <stdint.h>
#include <chrono>
#include <ratio>

class Window {
public:
	void open(const char* Title, uint32_t Width, uint32_t Height, bool fullscreen);
	void close(void);

	bool should_close(void);
	
	void update_screen(void);
	void update_poll_events(void);

	void set_input_callback(GLFWcursorposfun MouseCallback);

	bool get_key(uint32_t KeyCode);

	void set_visibility(bool vis);

private:
	GLFWwindow* _handle;

	int32_t _width;
	int32_t _height;

	friend class UIController;
};

#endif