#include "bitboard.h"

// int side is the attacking side
bool square_attacked(int side, int square) {

    if (side == white) {
        // Pawns
        if ( pawnAttacks[black][square] & bitboards[P] ) return true;
    } else {

    }

    return false;
}