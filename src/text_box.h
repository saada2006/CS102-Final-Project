#pragma once

#include "buffer.h"
#include "vtx_array.h"

#include <glm/glm.hpp>

#include <string>
#include <vector>

struct TextBox {
public:
    void gen_vtx_array(const std::string& text, const glm::vec2& center, float font_scale);    
    void gen_vtx_array(const std::string& text, const glm::vec2& center, const glm::vec2& font_scale);    

    void free();

    Buffer _buf;
    VertexArray _vtx_arr;

    int _num_triangles;
    std::vector<glm::vec2> _raw;
};