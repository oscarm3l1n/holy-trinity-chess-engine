#include <iostream>
#include "bitboard.h"
#include "attack.cpp"
#include "uci.cpp"


#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

void generate_bish(){
    u64 a = 0x0201000000000000;
    u64 b = 0x0402010000000000;
    u64 c = 0x0804020100000000;
    u64 d = 0x1008040201000000;
    u64 e = 0x2010080402010000;
    u64 f = 0x4020100804020100;
    u64 g = 0x8040201008040201;
    u64 h = 0x0080402010080402;
    u64 i = 0x0000804020100804;
    u64 j = 0x0000008040201008;
    u64 k = 0x0000000080402010;
    u64 l = 0x0000000000804020;
    u64 m = 0x0000000000008040;
    
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
}


int main(){
    parse_fen((char*)STARTFEN);
    print_board();
    print_bitboard(occupancy[both]);
    return 0;
}