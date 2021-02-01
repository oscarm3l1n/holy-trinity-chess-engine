#include "bitboard.h"



// leaper pieces
u64 pawnAttacks[2][64]; // not the same for black and white
u64 knightAttacks[64];
u64 kingAttacks[64];

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
u64 generate_pawn_attacks(bool isWhite, int square){
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

// same issues as for pawn, but this time need to avoid 
// a AND b file as well as g AND h file
u64 generate_knight_attacks(int square){
    const u64 withoutGHfile = 4557430888798830399ULL;
    const u64 withoutABfile = 18229723555195321596ULL;
    const u64 withoutAfile = 18374403900871474942ULL;
    const u64 withoutHfile = 9187201950435737471ULL;

    u64 attacks = 0ULL;
    u64 temp_bb = 0ULL;
    set_bit(temp_bb, square);
    if ((temp_bb >> 17) & withoutHfile)    attacks |= (temp_bb >> 17);
    if ((temp_bb >> 15) & withoutAfile)    attacks |= (temp_bb >> 15);
    if ((temp_bb >> 10) & withoutGHfile)    attacks |= (temp_bb >> 10);
    if ((temp_bb >> 6) & withoutABfile)     attacks |= (temp_bb >> 6);

    if ((temp_bb << 17) & withoutAfile)    attacks |= (temp_bb << 17);
    if ((temp_bb << 15) & withoutHfile)    attacks |= (temp_bb << 15);
    if ((temp_bb << 10) & withoutABfile)    attacks |= (temp_bb << 10);
    if ((temp_bb << 6) & withoutGHfile)     attacks |= (temp_bb << 6);

    return attacks;
}