#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include "board.h"
#include "buffer.h"
#include "game_state.h"
#include "user_input.h"
#include "shader.h"
#include "texture.h"
#include "window.h"
#include "vtx_array.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class UIController {
public:
    UIController();
    ~UIController();

    void render_game(const Board& board, GameState game_state);

    UserInput poll_user_input();

    bool window_open();
private:
    UserInput poll_current_input();

    int gen_tiles(VertexArray& tile_arr, Buffer& tile_buf);
    glm::vec2 get_tile_offset(int i, int j);

    Window _window;
    int _width, _height;

    UserInput _last_input;

    ShaderRasterization _tile_shader;
    glm::mat4 _tile_transform;
    
    Texture2D _bitmap_font;
    ShaderRasterization _bitmap_shader;
};

#endif