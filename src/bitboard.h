#pragma once

#include <iostream>
#include "enum.h"

#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define get_bit(bitboard, square) (((bitboard) >> (square)) & 1ULL)
#define clear_bit(bitboard, square) ((bitboard) &= ~(1ULL << square))

void print_bitboard(u64 bitboard){
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

int count_bits(u64 bitboard){
    int counter = 0;
    while (bitboard){
        bitboard &= bitboard - 1;
        counter++;
    }
    return counter;
}

int get_index(u64 bitboard){
    if (bitboard){
        return count_bits((bitboard & -bitboard) - 1);
    } else {
        return -1;
    }
}

void print_board(){
    for (int rank = 0; rank < 8; ++rank) {
        for( int file = 0; file < 8; ++file) {
            int square = 8 * rank + file;
            int piece = noPiece;
            if (!file)
                std::cout << 8 - rank << " ";

            for (int p = P; p <= k; p++) {
                if ( get_bit(bitboards[p], square) ){
                    piece = p;
                }
            }
            std::cout << " " << ((piece == noPiece) ? '.' : asciiPieces[piece]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "   a b c d e f g h" << std::endl;
    std::cout << "\n";
    std::cout << "side: " << ((side == white) ? "white" : "black") << std::endl;
    std::cout << "enpass: " << ((enPassant != noSquare) ? squareToCoord[enPassant] : "no") << std::endl;
    std::cout << "Castle: " << 
                ((castlingRights & wk) ? 'K' : '-') <<
                ((castlingRights & wq) ? 'Q' : '-') <<
                ((castlingRights & bk) ? 'k' : '-') <<
                ((castlingRights & bq) ? 'q' : '-') << std::endl;
    printf("\n\n");

}
