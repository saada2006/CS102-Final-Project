#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H

#include "board.h"
#include "movement_input.h"

class LogicController {
public:
    // Constructor
    LogicController();

    // What do we do when the user moves in a certain direction (up, down, left, right?)
    void accept_input(MovementInput input);

    // Just a normal getter
    Board get_board() const;
private:
    // Finds a random spot on the board and fills it with a 2 or a 4
    void fill_rand_num();

    // Initialize the rng
    void init_rng();
    // Generate a random integer in [mi, ma)
    int gen_random_num(int mi, int ma); // ma is not inclusive!

    // for an array of integers, a0, a1, a2, a3, this algorithm will remove all 0s in the area and move elements to the left
    bool make_all_consecutive(int* row);
    // if we can combine numbers of the same value in the arrow (e.g. 8 with 8), then this function handles that
    bool collapse_row(int* row);
    // does collapse row on each board
    bool collapse_board();

    // these flip the board 
    void reverse_board_horizontal();
    // technically this is a transpose of the matrix rather than a flip but whatever
    void reverse_board_vertical();

    Board _board;
    bool _updated;
};

#endif