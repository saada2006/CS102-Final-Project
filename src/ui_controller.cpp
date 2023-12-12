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
}

UIController::~UIController() {
    _window.close();
}

void UIController::render_board(const Board& board) {
    // render and swap buffers
    std::cout << "\n\n\n";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << board._num[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout.flush();

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

bool UIController::window_open() {
    return !_window.should_close();
}
