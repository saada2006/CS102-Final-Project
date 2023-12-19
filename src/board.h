#ifndef BOARD_H
#define BOARD_H

const int BOARD_SIZE = 4;

struct Board {
public:
    void clear();

    int _num[BOARD_SIZE][BOARD_SIZE];
};

#endif