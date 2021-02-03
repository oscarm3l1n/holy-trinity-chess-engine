#include <iostream>
#include "bitboard.h"
#include "attack.cpp"
#include "uci.cpp"
#include "init.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define FOR(n) for(int i = 0; i < n; i++)

int main(){
    init();

    parse_fen( (char*) STARTFEN);
    print_board();

    FOR(64){
        std::cout << "Square: " << squareToCoord[i] << std::endl;
        print_bitboard(get_rook_attacks(i, white));
        getchar();
    }

    return 0;
}