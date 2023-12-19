#include "logic_controller.h"

#include "board.h"
#include "user_input.h"

#include <algorithm>
#include <iostream>

#include <stdlib.h>
#include <time.h>

const int WINNING_NUMBER = 64;

LogicController::LogicController() {
    init_rng();

    restart();
}

void LogicController::restart() {
    _game_state = GAME_STATE_IN_PROGRESS;
    
    _board.clear();
    try_fill_rand_num();
    try_fill_rand_num();
}


void LogicController::accept_input(UserInput input) {
    if(input == UINPUT_RESET) {
        restart();
        return;
    }

    if(_game_state != GAME_STATE_IN_PROGRESS) {
        return;
    }

    // only add random numbers in conditions where the squares actually update
    if(move_board(input, _board)) {
        try_fill_rand_num();
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(_board._num[i][j] == WINNING_NUMBER) {
                std::cout << "Player has won the game!" << std::endl;
                _game_state = GAME_STATE_WON;
                return;
            }
        }
    }

    std::vector<UserInput> attempt_moves = {
        UINPUT_MOVE_LEFT, UINPUT_MOVE_RIGHT, UINPUT_MOVE_DOWN, UINPUT_MOVE_UP
    };

    bool lost_game = true;
    for(auto attempt : attempt_moves) {
        Board temp_board = _board;
        if(move_board(attempt, temp_board)) {
            lost_game = false;
            break;
        }
    }

    if(lost_game) {
        std::cout << "Player has lost game!" << std::endl;
        _game_state = GAME_STATE_LOST;
    }
}

bool LogicController::move_board(UserInput input, Board& temp_board) {
    bool updated = false;

    if(input == UINPUT_NONE) {
        updated = false;
    } else if(input == UINPUT_MOVE_LEFT) {
        updated = collapse_board(temp_board);
    } else if(input == UINPUT_MOVE_RIGHT) {
        reverse_board_horizontal(temp_board);
        updated = collapse_board(temp_board);
        reverse_board_horizontal(temp_board);
    } else if(input == UINPUT_MOVE_UP) {
        reverse_board_vertical(temp_board);
        reverse_board_horizontal(temp_board);
        updated = collapse_board(temp_board);
        reverse_board_horizontal(temp_board);
        reverse_board_vertical(temp_board);
    } else if(input == UINPUT_MOVE_DOWN) {
        reverse_board_vertical(temp_board);
        updated = collapse_board(temp_board);
        reverse_board_vertical(temp_board);
    } else {
        std::cout << "Unrecog input " << input << std::endl;
        abort();
    }

    return updated;
}


Board LogicController::get_board() const {
    return _board;
}

GameState LogicController::get_game_state() const {
    return _game_state;
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

bool LogicController::collapse_board(Board& temp_board) {
    bool any_row_changed = false;
    for(int i = 0; i < BOARD_SIZE; i++) {
        if(collapse_row(temp_board._num[i])) {
            any_row_changed = true;
        }
    }
    return any_row_changed;
}

void LogicController::reverse_board_horizontal(Board& temp_board) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        std::reverse(temp_board._num[i], temp_board._num[i] + BOARD_SIZE);
    }
}  

void LogicController::reverse_board_vertical(Board& temp_board) {
    // transpose the board
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = i + 1; j < BOARD_SIZE; j++) {
            std::swap(temp_board._num[i][j], temp_board._num[j][i]);
        }
    }
}

void LogicController::init_rng() {
    std::random_device rand_dev;
    _rng.seed(rand_dev());
}


void LogicController::try_fill_rand_num() {
    std::vector<std::pair<int, int>> open_slots;

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(_board._num[i][j] == 0) {
                open_slots.emplace_back(i, j);
            }
        }
    }

    if(open_slots.size() > 0) {
        int idx = gen_random_num(0, open_slots.size());

        int i = open_slots[idx].first;
        int j = open_slots[idx].second;

        int val = gen_random_num(1, 3);
        _board._num[i][j] = (1 << val);

        std::cout << "Picking " << i << " " << j << std::endl;
    } else {
        std::cout << "No empty square found!" << std::endl;
    }
}

int LogicController::gen_random_num(int minimum, int maximum) {
    std::uniform_int_distribution<int> idist(minimum, maximum - 1);

    return idist(_rng);
}
