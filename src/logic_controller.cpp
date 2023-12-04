#include "logic_controller.h"

#include "board.h"
#include "movement_input.h"

#include <algorithm>
#include <iostream>

#include <stdlib.h>
#include <time.h>

LogicController::LogicController() {
    init_rng();
    
    fill_rand_num();
    fill_rand_num();
}

void LogicController::accept_input(MovementInput input) {
    bool did_move = false;

    if(input == MOV_L) {
        did_move = collapse_board();
    } else if(input == MOV_R) {
        reverse_board_horizontal();
        did_move = collapse_board();
        reverse_board_horizontal();
    } else if(input == MOV_U) {
        reverse_board_vertical();
        did_move = collapse_board();
        reverse_board_vertical();
    } else if(input == MOV_D) {
        reverse_board_vertical();
        reverse_board_horizontal();
        did_move = collapse_board();
        reverse_board_horizontal();
        reverse_board_vertical();
    } else {
        std::cout << "Unrecog input " << input << std::endl;
        abort();
    }

    if(did_move) {
        fill_rand_num();
    }

    
}

Board LogicController::get_board() const {
    return _board;
}

bool LogicController::make_all_consecutive(int* row) {
    bool any_change = false;

    int write_loc = 0;
    for(int i = 0; i < BOARD_SIZE; i++) {
        if(row[i] != 0) {
            if(i != write_loc) {
                any_change = true;
            }

            int val = row[i];
            row[i] = 0;
            row[write_loc] = val;
            write_loc++;
        }
    }

    return any_change;
}


bool LogicController::collapse_row(int* row) {
    bool any_change = make_all_consecutive(row);

    for(int i = 0; i < BOARD_SIZE - 1; i++) {
        if(row[i] == row[i + 1]) {
            row[i] *= 2;
            row[i + 1] = 0;
            any_change = true;
        }
    }

    make_all_consecutive(row);

    return any_change;
}

bool LogicController::collapse_board() {
    bool any_row_changed = false;
    for(int i = 0; i < BOARD_SIZE; i++) {
        if(collapse_row(_board._num[i])) {
            any_row_changed = true;
        }
    }
    return any_row_changed;
}

void LogicController::reverse_board_horizontal() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        std::reverse(_board._num[i], _board._num[i] + BOARD_SIZE);
    }
}  

void LogicController::reverse_board_vertical() {
    // transpose the board
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = i + 1; j < BOARD_SIZE; j++) {
            std::swap(_board._num[i][j], _board._num[j][i]);
        }
    }
}

void LogicController::init_rng() {
    srand(time(nullptr));
}


void LogicController::fill_rand_num() {
    while(true) {
        int row = gen_random_num(0, BOARD_SIZE);
        int col = gen_random_num(0, BOARD_SIZE);

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
