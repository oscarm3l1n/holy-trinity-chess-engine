#include <iostream>
#include "bitboard.h"
#include "attack.cpp"
#include "uci.cpp"
#include "init.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define FOR(n) for(int i = 0; i < n; i++)

// https://lichess.org/editor
// to create custom FEN's
int main(){
    init();
    init_leaper_attacks();

    parse_fen( (char*) "8/8/ppp5/8/8/3b4/8/8 w - - 0 1");
    print_board();

    print_attacked_squares(black);


    return 0;
}