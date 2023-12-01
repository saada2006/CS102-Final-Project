#include "logic_controller.h"

#include "board.h"
#include "movement_input.h"

#include <stdlib.h>
#include <time.h>

LogicController::LogicController() {
    init_rng();
    
    fill_rand_num();
    fill_rand_num();
}

void LogicController::accept_input(MovementInput input) {

}

Board LogicController::get_board() const {
    return _board;
}

void LogicController::init_rng() {
    srand(time(nullptr));
}


void LogicController::fill_rand_num() {
    while(true) {
        int row = gen_random_num(0, 4);
        int col = gen_random_num(0, 4);

        if(_board._num[row][col] != 0) {
            continue;
        } else {
            int val = gen_random_num(1, 3);
            _board._num[row][col] = (1 << val);
            break;
        }
    }
}

int LogicController::gen_random_num(int mi, int ma) {
    int val = rand();

    val %= (ma - mi);
    val += mi;

    return val;
}
