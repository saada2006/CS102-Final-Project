#include "ui_controller.h"

#include "board.h"

#include <iostream>

void UIController::render_board(const Board& board) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << board._num[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout.flush();
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
