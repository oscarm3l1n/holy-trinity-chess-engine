#pragma once

#include <iostream>
#include "enum.h"
#define u64 unsigned long long

#define set_bit(bitboard, square) ((bitboard) |= (1ULL << square))
#define get_bit(bitboard, square) (((bitboard) >> (square)) & 1ULL)
#define clear_bit(bitboard, square) ((bitboard) &= ~(1ULL << square))


void print_bitboard(u64 bitboard){
    printf("\n\n");
    for (int rank = 0; rank < 8; ++rank){
        for (int file = 0; file < 8; ++file){
            int square = 8 * rank + file;
            if (!file)
                std::cout << 8 - rank << "  ";
            std::cout << get_bit(bitboard, square) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n   a b c d e f g h\n\n";
}

/*
    0 0 0 0 0 0 1 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
*/

/*
    1 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
*/

