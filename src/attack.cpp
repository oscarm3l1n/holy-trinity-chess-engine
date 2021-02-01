#include "bitboard.h"



// leaper pieces
u64 pawnAttackMask[64];
u64 knightAttackMask[64];
u64 kingAttackMask[64];

void init_leaper_attacks(){

}

void init_slider_attacks(){

}

// generate attack mask for pawns. for example
// a pawn on e4 should attack d5 and f5. Therefore we need to 
// shift 7 and 9 bits.
// LOOK OUT for shifting bits to wrong side, i.e. if pawn is  on a2
// it can not attack on h4 like it will happen if you shift without
// protection
// Solution #1
// Create a static u64 that has the A file as 0 and logic & with that file
u64 generate_pawn_attack_mask(bool isWhite, int square){
    const u64 withoutAfile = 18374403900871474942ULL;
    const u64 withoutHfile = 9187201950435737471ULL;
    u64 attacks = 0ULL;
    u64 temp_bb = 0ULL;
    set_bit(temp_bb, square);
    if (isWhite){
        if ((temp_bb >> 9) & withoutHfile)
            attacks |= (temp_bb >> 9);
        if ((temp_bb >> 7) & withoutAfile)
            attacks |= (temp_bb >> 7);
    } else {
        
    }
    return attacks;
}