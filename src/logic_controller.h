#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H

#include "board.h"
#include "movement_input.h"

class LogicController {
public:
    LogicController();

    void accept_input(MovementInput input);

    Board get_board() const;
private:
    void fill_rand_num();

    void init_rng();
    int gen_random_num(int mi, int ma); // ma is not inclusive!

    Board _board;
};

#endif