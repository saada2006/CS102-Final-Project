#include "board.h"
#include "logic_controller.h"
#include "ui_controller.h"

#include <iostream>

int main() {
    LogicController logic_con;
    UIController ui_con;

    float x = 1.0;
    while(ui_con.window_open()) {
        glClearColor(x, x, x, 1.0);
        x = 1 - x;

        glClear(GL_COLOR_BUFFER_BIT);

        //logic_con.accept_input(ui_con.poll_user_input());
        ui_con.render_board(logic_con.get_board());
    }
    
    return 0;
}