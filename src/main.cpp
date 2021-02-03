#include <iostream>
#include "bitboard.h"
#include "attack.cpp"
#include "uci.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

int main(){
    parse_fen((char*)STARTFEN);
    // set_bit(bitboards[p], d5);
    // set_bit(bitboards[P], e4);
    clear_bit(bitboards[P], g2);
    init_leaper_attacks();
    print_board();
    std::cout << (square_attacked(white, h3) ? "Yes" : "No") << std::endl;;

    return 0;
}