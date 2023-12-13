#include "text_box.h"

#include <GL/glew.h>

#include <vector>

const int BITMAP_WIDTH = 16;
const float BITMAP_CHAR_SIZE = 1.0f / BITMAP_WIDTH;

void TextBox::gen_vtx_array(const std::string& text, const glm::vec2& center, float font_scale) {
    std::vector<glm::vec2> text_data;

    for(int i = 0; i < text.size(); i++) {
        char c = text[i];

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
            text_base[j] = (text_base[j] + glm::vec2(i, 0)) * font_scale;
        }

        for(auto& v : text_base) {
            text_data.push_back(v);
        }
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

void TextBox::free() {
    _vtx_arr.Free();
    _buf.Free();
}
