#include "text_box.h"

#include <GL/glew.h>

#include <vector>

const int BITMAP_WIDTH = 16;
const float BITMAP_CHAR_SIZE = 1.0f / BITMAP_WIDTH;

void TextBox::gen_vtx_array(const std::string& text, const glm::vec2& center, const glm::vec2& font_scale) {
    auto current_center = glm::vec2(text.size() / 2.0f, 0.5f) * font_scale; // does not work properly in case of newlines, but idc enough to implement this properly
    auto offset = center - current_center;

    std::vector<glm::vec2> text_data;

    float v_offset = 0.0f;
    float h_offset = 0.0f;
    for(int i = 0; i < text.size(); i++) {
        char c = text[i];

        if(c == '\n') {
            v_offset--;
            h_offset = 0.0f;
            continue;
        } else if(c == ' ') {
            h_offset += 0.4f;
            continue;
        }

        int row = c / BITMAP_WIDTH;
        int col = c % BITMAP_WIDTH;

        glm::vec2 upper_left = glm::vec2(col, row) * BITMAP_CHAR_SIZE;

        std::vector<glm::vec2> text_base = {
            { 0.0f,  0.0f}, {upper_left.x,                    upper_left.y + BITMAP_CHAR_SIZE},
            { 1.0f,  0.0f}, {upper_left.x + BITMAP_CHAR_SIZE, upper_left.y + BITMAP_CHAR_SIZE},
            { 1.0f,  1.0f}, {upper_left.x + BITMAP_CHAR_SIZE, upper_left.y                   },
            { 1.0f,  1.0f}, {upper_left.x + BITMAP_CHAR_SIZE, upper_left.y                   },
            { 0.0f,  1.0f}, {upper_left.x,                    upper_left.y                   },
            { 0.0f,  0.0f}, {upper_left.x,                    upper_left.y + BITMAP_CHAR_SIZE},
        };

        for(int j = 0; j < text_base.size(); j += 2) {
            text_base[j] = (text_base[j] + glm::vec2(h_offset, v_offset)) * font_scale + offset;
        }

        for(auto& v : text_base) {
            text_data.push_back(v);
        }

        h_offset += 0.7f;
    }

    _buf.CreateBinding(BUFFER_TARGET_ARRAY);
    _buf.UploadData(text_data, GL_STATIC_DRAW);

    _vtx_arr.CreateBinding();
    _vtx_arr.CreateStream(0, 4, 0);

    _num_triangles = text_data.size() / 2;

    for(int i = 0; i < text_data.size(); i += 2) {
        _raw.push_back(text_data[i]);
    }
}

void TextBox::gen_vtx_array(const std::string& text, const glm::vec2& center, float font_scale) {
    gen_vtx_array(text, center, glm::vec2(font_scale));
}

void TextBox::free() {
    _vtx_arr.Free();
    _buf.Free();
}
