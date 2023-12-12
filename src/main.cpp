#include "board.h"
#include "logic_controller.h"
#include "ui_controller.h"

#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Executing in location " << argv[0] << '\n'; 

    LogicController logic_con;
    UIController ui_con;

    while(ui_con.window_open()) {
        logic_con.accept_input(ui_con.poll_user_input());
        ui_con.render_board(logic_con.get_board());
    }
    
    return 0;
}