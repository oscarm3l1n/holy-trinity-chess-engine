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

// slider pieces
u64 rookAttacks[64] = {
    72340172838076926ULL,
    144680345676153597ULL,
    289360691352306939ULL,
    578721382704613623ULL,
    1157442765409226991ULL,
    2314885530818453727ULL,
    4629771061636907199ULL,
    9259542123273814143ULL,
    72340172838141441ULL,
    144680345676217602ULL,
    289360691352369924ULL,
    578721382704674568ULL,
    1157442765409283856ULL,
    2314885530818502432ULL,
    4629771061636939584ULL,
    9259542123273813888ULL,
    72340172854657281ULL,
    144680345692602882ULL,
    289360691368494084ULL,
    578721382720276488ULL,
    1157442765423841296ULL,
    2314885530830970912ULL,
    4629771061645230144ULL,
    9259542123273748608ULL,
    72340177082712321ULL,
    144680349887234562ULL,
    289360695496279044ULL,
    578721386714368008ULL,
    1157442769150545936ULL,
    2314885534022901792ULL,
    4629771063767613504ULL,
    9259542123257036928ULL,
    72341259464802561ULL,
    144681423712944642ULL,
    289361752209228804ULL,
    578722409201797128ULL,
    1157443723186933776ULL,
    2314886351157207072ULL,
    4629771607097753664ULL,
    9259542118978846848ULL,
    72618349279904001ULL,
    144956323094725122ULL,
    289632270724367364ULL,
    578984165983651848ULL,
    1157687956502220816ULL,
    2315095537539358752ULL,
    4629910699613634624ULL,
    9259541023762186368ULL,
    143553341945872641ULL,
    215330564830528002ULL,
    358885010599838724ULL,
    645993902138460168ULL,
    1220211685215703056ULL,
    2368647251370188832ULL,
    4665518383679160384ULL,
    9259260648297103488ULL,
    18302911464433844481ULL,
    18231136449196065282ULL,
    18087586418720506884ULL,
    17800486357769390088ULL,
    17226286235867156496ULL,
    16077885992062689312ULL,
    13781085504453754944ULL,
    9187484529235886208ULL,
};

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

u64 get_rook_attacks(int square){
    return rookAttacks[square];
}

void generate_rook_attacks(){
    u64 a = 0xff;
    u64 b = 0xff00;
    u64 c = 0xff0000;
    u64 d = 0xff000000;
    u64 e = 0xff00000000;
    u64 f = 0xff0000000000;
    u64 g = 0xff000000000000;
    u64 h = 0xff00000000000000;
    u64 file[8] = {a,b,c,d,e,f,g,h};

    u64 aa = 0x0101010101010101;
    u64 bb = 0x0202020202020202;
    u64 cc = 0x0404040404040404;
    u64 dd = 0x0808080808080808;
    u64 ee = 0x1010101010101010;
    u64 ff = 0x2020202020202020;
    u64 gg = 0x4040404040404040;
    u64 hh = 0x8080808080808080;
    u64 rank[] = {aa,bb,cc,dd,ee,ff,gg,hh};

    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            int square = 8*i+j;
            // std::cout << "square: " << squareToCoord[square] << std::endl;
            u64 result = file[i] | rank[j];
            clear_bit(result, square);
            // print_bitboard(result);
            // getchar();
            std::cout << result << "ULL," << std::endl;
        }
    }
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