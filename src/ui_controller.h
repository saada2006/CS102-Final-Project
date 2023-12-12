#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include "board.h"
#include "buffer.h"
#include "movement_input.h"
#include "shader.h"
#include "window.h"
#include "vtx_array.h"

#include <glm/glm.hpp>

class UIController {
public:
    UIController();
    ~UIController();

    void render_board(const Board& board);

    MovementInput poll_user_input();

    bool window_open();
private:
    MovementInput poll_current_input();

    int gen_tiles(VertexArray& tile_arr);

    Window _window;
    MovementInput _last_input;

    ShaderRasterization _tile_shader;
    glm::vec3 _tile_color;
    
};

#endif