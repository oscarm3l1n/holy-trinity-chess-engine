#include <iostream>

#define u64 unsigned long long

#define set_bit(bitboard, square) ((bitboard) |= (1ULL << square))
#define get_bit(bitboard, square) (((bitboard) >> (square)) & 1ULL)
#define clear_bit(bitboard, square) ((bitboard) &= ~(1ULL << square))

enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

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