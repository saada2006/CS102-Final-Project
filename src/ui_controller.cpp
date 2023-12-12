#include "ui_controller.h"

#include "board.h"

#include <iostream>

bool glew_already_init = false;
UIController::UIController() : _last_input(MOV_NONE) {
    _window.open("2048", 640, 480, false);

    if(!glew_already_init && glewInit() != GLEW_OK) {
        std::cerr << "GLEW INITIATION FAILED!";
        abort();
    }

    glew_already_init = true;

    _tile_shader.CompileFiles("./res/tile.vert", "./res/tile.frag");
    _tile_scale = 0.8;
}

UIController::~UIController() {
    _window.close();
}

void UIController::render_board(const Board& board) {
    // render and swap buffers
    /*
    std::cout << "\n\n\n";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << board._num[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout.flush();
    */


   VertexArray tile_arr;
   tile_arr.CreateBinding();
   int n_tile_triangles = gen_tiles(tile_arr);
   _tile_shader.CreateBinding();
   _tile_color = glm::vec3(sin(glfwGetTime()) * 0.5 + 0.5);
   _tile_shader.LoadVector3F32("tile_color", _tile_color);
   glDrawArrays(GL_TRIANGLES, 0, n_tile_triangles);
   tile_arr.Free();

    std::cout << glGetError() << std::endl;

    _window.update_screen();
    _window.update_poll_events();
}

MovementInput UIController::poll_user_input() {
    MovementInput implied_input = MOV_NONE;

    MovementInput current_input = poll_current_input();
    if(current_input != _last_input) {
        implied_input = current_input;
    }
    _last_input = current_input;

    return implied_input;
}


bool UIController::window_open() {
    return !_window.should_close();
}

int UIController::gen_tiles(VertexArray& tile_arr) {
    Buffer tile_buf;

    tile_buf.CreateBinding(BUFFER_TARGET_ARRAY);
    
    std::vector<glm::vec2> tile_base = {
        {-1.0f, -1.0f},
        { 1.0f, -1.0f},
        { 1.0f,  1.0f},
        { 1.0f,  1.0f},
        {-1.0f,  1.0f},
        {-1.0f, -1.0f},
    };

    std::vector<glm::vec2> tiles;

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            glm::vec2 offset = vec2(i + 0.5f, j + 0.5f) / (float)BOARD_SIZE;
            offset = offset * 2.0f - 1.0f;

            float adjusted_scale = _tile_scale / BOARD_SIZE;
            for(auto& v : tile_base) {
                tiles.push_back(adjusted_scale * v + offset);
            }

        }
    }

    tile_buf.UploadData(tiles, GL_STATIC_DRAW);

    tile_arr.CreateStream(0, 2, 0);
    //tile_buf.Free();

    return tiles.size();
}   

MovementInput UIController::poll_current_input() {
    if(_window.get_key(GLFW_KEY_W)) {
        return MOV_U;
    } else if(_window.get_key(GLFW_KEY_S)) {
        return MOV_D;
    } else if(_window.get_key(GLFW_KEY_D)) {
        return MOV_R;
    } else if(_window.get_key(GLFW_KEY_A)) {
        return MOV_L;
    } else {
        return MOV_NONE;
    }
}