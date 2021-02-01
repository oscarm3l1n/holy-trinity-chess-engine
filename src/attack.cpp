#include "bitboard.h"



// leaper pieces
u64 pawnAttacks[2][64]; // not the same for black and white
u64 knightAttacks[64];
u64 kingAttacks[64];


u64 generate_pawn_attacks(int side, int square){
    // helps with not shifting the bit into the wrong squares
    const u64 withoutAfile = 18374403900871474942ULL;
    const u64 withoutHfile = 9187201950435737471ULL;
    u64 attacks = 0ULL;
    u64 tempBitboard = 0ULL;
    set_bit(tempBitboard, square);
    if (side){
        // white
        if ((tempBitboard >> 9) & withoutHfile)
            attacks |= (tempBitboard >> 9);
        if ((tempBitboard >> 7) & withoutAfile)
            attacks |= (tempBitboard >> 7);
    } else {
        // black
        if ((tempBitboard << 9) & withoutAfile)
            attacks |= (tempBitboard << 9);
        if ((tempBitboard << 7) & withoutHfile)
            attacks |= (tempBitboard << 7);
    }
    return attacks;
}

u64 generate_knight_attacks(int square){
    // helps with not shifting the bit into the wrong squares
    const u64 withoutGHfile = 4557430888798830399ULL;
    const u64 withoutABfile = 18229723555195321596ULL;
    const u64 withoutAfile = 18374403900871474942ULL;
    const u64 withoutHfile = 9187201950435737471ULL;

    u64 attacks = 0ULL;
    u64 tempBitboard = 0ULL;
    set_bit(tempBitboard, square);
    if ((tempBitboard >> 17) & withoutHfile)    attacks |= (tempBitboard >> 17);
    if ((tempBitboard >> 15) & withoutAfile)    attacks |= (tempBitboard >> 15);
    if ((tempBitboard >> 10) & withoutGHfile)    attacks |= (tempBitboard >> 10);
    if ((tempBitboard >> 6) & withoutABfile)     attacks |= (tempBitboard >> 6);

    if ((tempBitboard << 17) & withoutAfile)    attacks |= (tempBitboard << 17);
    if ((tempBitboard << 15) & withoutHfile)    attacks |= (tempBitboard << 15);
    if ((tempBitboard << 10) & withoutABfile)    attacks |= (tempBitboard << 10);
    if ((tempBitboard << 6) & withoutGHfile)     attacks |= (tempBitboard << 6);

    return attacks;
}

u64 generate_king_attacks(int square){
    u64 attacks = 0ULL;
    
    return attacks;
}

void init_leaper_attacks(){
    // pawns
    for(int square = 0; square < 64; ++square){
        pawnAttacks[white][square] = generate_pawn_attacks(white, square);
        pawnAttacks[black][square] = generate_pawn_attacks(black, square);
        knightAttacks[square] = generate_knight_attacks(square);
        kingAttacks[square] = generate_king_attacks(square);
    }
}

void init_slider_attacks(){

}