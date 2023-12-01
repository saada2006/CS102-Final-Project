#include "board.h"
#include "logic_controller.h"
#include "ui_controller.h"

#include <iostream>

int main() {
    LogicController logic_con;
    UIController ui_con;

    while(true) {
        ui_con.render_board(logic_con.get_board());
        logic_con.accept_input(ui_con.poll_user_input());
    }

    return 0;
}