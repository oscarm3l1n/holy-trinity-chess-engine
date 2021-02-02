#include <iostream>
#include "bitboard.h"
#include "attack.cpp"
#include "uci.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

int main(){
    parse_fen((char*)STARTFEN);
    print_board();
    print_bitboard(occupancy[both]);
    return 0;
}