#include <iostream>
// #include "bitboard.h"
// #include "attack.cpp"
// #include "uci.cpp"
// #include "init.cpp"
#include "moves.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define FOR(n) for(int i = 0; i < n; i++)

// https://lichess.org/editor
// to create custom FEN's
int main(){
    init();
    init_leaper_attacks();

    std::vector<int> moveList;

    parse_fen( (char*) "r3k2r/pp1ppppp/6q1/8/3pP3/8/8/Q1Q5 b kq e3 0 1");
    print_board();

    generate_moves(moveList);


    return 0;
}