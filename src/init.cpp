#include "enum.h"

void init(){
    // init attack

    for (int piece = P; piece <= k; piece++){
        bitboards[piece] = 0ULL;
    }
    occupancy[white] = 0ULL;
    occupancy[black] = 0ULL;
    occupancy[both] = 0ULL;

    enPassant = noSquare;
    castlingRights = 0;
    side = white;
}