#include <iostream>
#include "bitboard.h"
#include "attack.cpp"

void u64_print_without_file(){
    // a file
    u64 temp_bb = 0ULL;
    for(int rank = 0; rank < 8; ++rank){
        for(int file = 0; file < 8; ++file){
            int square = 8 * rank + file;
            if (file < 7)
                set_bit(temp_bb, square);
        }
    }
    print_bitboard(temp_bb);
    std::cout << "temp_bb: "<< temp_bb << "ULL" << std::endl;
}

int main(){
    
    u64 temp = 0ULL;
    for(int sq = 0; sq < 64; ++sq){
        std::cout << "square: " << squareToCoord[sq] << std::endl;
        temp = generate_pawn_attack_mask(true, sq);
        print_bitboard(temp);
        getchar();
    }
    // u64_print_without_file();

    return 0;
}