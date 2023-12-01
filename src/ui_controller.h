#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include "board.h"
#include "movement_input.h"

class UIController {
public:
    void render_board(const Board& board);

    MovementInput poll_user_input();
private:
};

#endif