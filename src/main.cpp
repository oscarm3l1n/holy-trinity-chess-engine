#include <iostream>
#include "bitboard.h"
#include "attack.cpp"
#include "uci.cpp"
#include "init.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


int main(){
    init();

    parse_fen( (char*) STARTFEN);
    print_board();

    for(int i = 0; i < 64; i++){
        std::cout << "Square: " << squareToCoord[i] << std::endl;
        print_bitboard(get_bishop_attacks(i, white));
        getchar();
    }

    return 0;
}