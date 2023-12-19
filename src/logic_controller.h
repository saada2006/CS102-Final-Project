#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H

#include "board.h"
#include "movement_input.h"

#include <random>

enum GameState {
    GAME_STATE_IN_PROGRESS,
    GAME_STATE_LOST,
    GAME_STATE_WON,
};

class LogicController {
public:
    // Constructor
    LogicController();

    // What do we do when the user moves in a certain direction (up, down, left, right?)
    void accept_input(UserInput input);

    // Just a normal getter
    Board get_board() const;
    GameState get_game_state() const;

    void restart();
private:
    // Finds a random spot on the board and fills it with a 2 or a 4
    void try_fill_rand_num();

    // Initialize the rng
    void init_rng();
    // Generate a random integer in [minimum, maximum)
    int gen_random_num(int minimum, int maximum); // maximum is not inclusive!

    // for an array of integers, a0, a1, a2, a3, this algorithm will remove all 0s in the area and move elements to the left
    bool make_all_consecutive(int* row);
    // if we can combine numbers of the same value in the arrow (e.g. 8 with 8), then this function handles that
    bool collapse_row(int* row);
    // does collapse row on each board
    bool collapse_board(Board& temp_board);

    // these flip the board 
    void reverse_board_horizontal(Board& temp_board);
    // technically this is a transpose of the matrix rather than a flip but whatever
    void reverse_board_vertical(Board& temp_board);

    bool move_board(UserInput input, Board& temp_board);

    Board _board;
    bool _updated;

    std::mt19937 _rng;

    GameState _game_state;
};

#endif