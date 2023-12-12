#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include "board.h"
#include "movement_input.h"
#include "window.h"

class UIController {
public:
    UIController();
    ~UIController();

    void render_board(const Board& board);

    MovementInput poll_user_input();

    bool window_open();
private:
    MovementInput poll_current_input();

    Window _window;
    MovementInput _last_input;
};

#endif