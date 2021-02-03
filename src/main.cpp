#include <iostream>
#include "bitboard.h"
#include "attack.cpp"
#include "uci.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

//RADERA FUNKTION OM DU VILL -erik
void generate_bish(){
    u64 empty = 0x0000000000000000;
    
    u64 a = 0x0201000000000000; //left down corner
    u64 b = 0x0402010000000000;
    u64 c = 0x0804020100000000;
    u64 d = 0x1008040201000000;
    u64 e = 0x2010080402010000;
    u64 f = 0x4020100804020100;
    u64 g = 0x8040201008040201; //middle down
    u64 h = 0x0080402010080402;
    u64 q = 0x0000804020100804;
    u64 p = 0x0000008040201008;
    u64 k = 0x0000000080402010;
    u64 l = 0x0000000000804020;
    u64 m = 0x0000000000008040; //right up corner
    
    u64 aa = 0x0000000000000102;
    u64 bb = 0x0000000000010204;
    u64 cc = 0x0000000001020408;
    u64 dd = 0x0000000102040810;
    u64 ee = 0x0000010204081020;
    u64 ff = 0x0001020408102040;
    u64 gg = 0x0102040810204080;
    u64 hh = 0x0204081020408000;
    u64 ii = 0x0408102040800000;
    u64 jj = 0x0810204080000000;
    u64 kk = 0x1020408000000000;
    u64 ll = 0x2040800000000000;
    u64 mm = 0x4080000000000000;

    u64 up[] = {cc, ii, kk, mm, empty};

    for (int i = 10; i < 64; ++i){
        for (int j = 0; j < 8; ++j){
            int square = 9*j+i;
            std::cout << "square: " << squareToCoord[square] << std::endl;
            u64  result =  h | up[j];
            clear_bit(result, square);
            print_bitboard(result);
            std::cout << result << "ULL," << std::endl << std::endl;
            getchar();
        }    
    }
}

int main(){
    parse_fen((char*)STARTFEN);
    // set_bit(bitboards[p], d5);
    // set_bit(bitboards[P], e4);
    clear_bit(bitboards[P], g2);
    init_leaper_attacks();
    print_board();
    std::cout << (square_attacked(white, h3) ? "Yes" : "No") << std::endl;;

    return 0;
}