#include <iostream>
#include "bitboard.h"

int main(){
    u64 bitboard = 0ULL;

    set_bit(bitboard, c8);
    print_bitboard(bitboard);

    std::cout << "Remove" << std::endl;
    clear_bit(bitboard, c8);
    print_bitboard(bitboard);

    printf("Bitboard: %lld\n", bitboard);
    return 0;
}