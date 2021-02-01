#include <iostream>
#include "bitboard.h"

int main(){

    #ifdef WIN64
        std::cout << "Aeee..." << std::endl;
    #else
        std::cout << "Tjena kexet" << std::endl;
    #endif

    u64 bitboard = 0ULL;

    printf("Bitboard: %lld\n", bitboard);
    return 0;
}