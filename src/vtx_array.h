// OLD CODE - DO NOT TOUCH THIS GARBAGE!
#pragma once

#include "opengl.h"
#include <stdint.h>

class VertexArray {
public:
	VertexArray(void);

	void CreateBinding(void);
	void FreeBinding(void);

	void CreateStream(uint32_t Index, uint32_t Elements, uint32_t Stride);

	void Free(void);
private:
	GLuint VertexArrayHandle;
};