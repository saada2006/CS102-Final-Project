#include "ui_controller.h"

#include "board.h"

#include <iostream>

bool glew_already_init = false;
UIController::UIController() {
    _window.open("2048", 1280, 720, true);

    if(!glew_already_init && glewInit() != GLEW_OK) {
        std::cerr << "GLEW INITIATION FAILED!";
        abort();
    }

    glew_already_init = true;
}

UIController::~UIController() {
    _window.close();
}

void UIController::render_board(const Board& board) {
    // render and swap buffers
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
    std::cout << "Please enter a choice:\n"
              << "\tMOV_U\t=\t" << MOV_U << '\n'
              << "\tMOV_D\t=\t" << MOV_D << '\n'
              << "\tMOV_R\t=\t" << MOV_R << '\n'
              << "\tMOV_L\t=\t" << MOV_L << '\n';
              
    std::cout.flush();

    int input;
    std::cin >> input;

    return (MovementInput)input;
}

bool UIController::window_open() {
    return !_window.should_close();
}
