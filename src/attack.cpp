#include "bitboard.h"

u64 rayNorth[64] = {
    0ULL,
    0ULL,
    0ULL,
    0ULL,
    0ULL,
    0ULL,
    0ULL,
    0ULL,
    1ULL,
    2ULL,
    4ULL,
    8ULL,
    16ULL,
    32ULL,
    64ULL,
    128ULL,
    257ULL,
    514ULL,
    1028ULL,
    2056ULL,
    4112ULL,
    8224ULL,
    16448ULL,
    32896ULL,
    65793ULL,
    131586ULL,
    263172ULL,
    526344ULL,
    1052688ULL,
    2105376ULL,
    4210752ULL,
    8421504ULL,
    16843009ULL,
    33686018ULL,
    67372036ULL,
    134744072ULL,
    269488144ULL,
    538976288ULL,
    1077952576ULL,
    2155905152ULL,
    4311810305ULL,
    8623620610ULL,
    17247241220ULL,
    34494482440ULL,
    68988964880ULL,
    137977929760ULL,
    275955859520ULL,
    551911719040ULL,
    1103823438081ULL,
    2207646876162ULL,
    4415293752324ULL,
    8830587504648ULL,
    17661175009296ULL,
    35322350018592ULL,
    70644700037184ULL,
    141289400074368ULL,
    282578800148737ULL,
    565157600297474ULL,
    1130315200594948ULL,
    2260630401189896ULL,
    4521260802379792ULL,
    9042521604759584ULL,
    18085043209519168ULL,
    36170086419038336ULL
};
u64 raySouth[64] = {

};
u64 rayWest[64] = {

};
u64 rayEast[64] = {

};

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
    if ((tempBitboard >> 17) & withoutHfile)     attacks |= (tempBitboard >> 17);
    if ((tempBitboard >> 15) & withoutAfile)     attacks |= (tempBitboard >> 15);
    if ((tempBitboard >> 10) & withoutGHfile)    attacks |= (tempBitboard >> 10);
    if ((tempBitboard >> 6) & withoutABfile)     attacks |= (tempBitboard >> 6);

    if ((tempBitboard << 17) & withoutAfile)     attacks |= (tempBitboard << 17);
    if ((tempBitboard << 15) & withoutHfile)     attacks |= (tempBitboard << 15);
    if ((tempBitboard << 10) & withoutABfile)    attacks |= (tempBitboard << 10);
    if ((tempBitboard << 6) & withoutGHfile)     attacks |= (tempBitboard << 6);

    return attacks;
}

u64 generate_king_attacks(int square){
    // helps with not shifting the bit into the wrong squares
    const u64 withoutAfile = 18374403900871474942ULL;
    const u64 withoutHfile = 9187201950435737471ULL;
    
    u64 attacks = 0ULL;
    u64 tempBitboard = 0ULL;
    set_bit(tempBitboard, square);
    if ((tempBitboard >> 1) & withoutHfile)       attacks |= (tempBitboard >> 1);
    if ((tempBitboard >> 7) & withoutAfile)       attacks |= (tempBitboard >> 7);
    if ((tempBitboard >> 8))                      attacks |= (tempBitboard >> 8);
    if ((tempBitboard >> 9) & withoutHfile)       attacks |= (tempBitboard >> 9);

    if ((tempBitboard << 1) & withoutAfile)       attacks |= (tempBitboard << 1);
    if ((tempBitboard << 7) & withoutHfile)       attacks |= (tempBitboard << 7);
    if ((tempBitboard << 8))                      attacks |= (tempBitboard << 8);
    if ((tempBitboard << 9) & withoutAfile)       attacks |= (tempBitboard << 9);

    return attacks;
}

// slider pieces
u64 generate_bishop_attacks(int square){
    return 0ULL;
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