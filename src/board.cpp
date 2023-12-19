#include "board.h"

void Board::clear() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            _num[i][j] = 0;
        }
    }
}