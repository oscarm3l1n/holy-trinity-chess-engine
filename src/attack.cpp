#include "bitboard.h"

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
u64 bishopAttacks[64] = {
    9241421688590303744ULL,     //a8
    36099303471056128ULL,       //b8
    141012904249856ULL,         //c8
    550848566272ULL,            //d8
    6480472064ULL,              //e8
    1108177604608ULL,           //f8
    283691315142656ULL,         //g8
    72624976668147712ULL,       //h8
    4620710844295151618ULL,     //a7
    9241421688590368773ULL,     //b7
    36099303487963146ULL,       //c7
    141017232965652ULL,         //d7
    1659000848424ULL,           //e7
    283693466779728ULL,         //f7
    72624976676520096ULL,       //g7
    145249953336262720ULL,      //h7
    2310355422147510788ULL,     //a6
    4620710844311799048ULL,     //b6
    9241421692918565393ULL,     //c6
    36100411639206946ULL,       //d6
    424704217196612ULL,         //e6
    72625527495610504ULL,       //f6
    145249955479592976ULL,      //g6
    290499906664153120ULL,      //h6
    1155177711057110024ULL,     //a5
    2310355426409252880ULL,     //b5
    4620711952330133792ULL,     //c5
    9241705379636978241ULL,     //d5
    108724279602332802ULL,      //e5
    145390965166737412ULL,      //f5
    290500455356698632ULL,      //g5
    580999811184992272ULL,      //h5
    577588851267340304ULL,      //a4
    1155178802063085600ULL,     //b4
    2310639079102947392ULL,     //c4
    4693335752243822976ULL,     //d4
    9386671504487645697ULL,     //e4
    326598935265674242ULL,      //f4
    581140276476643332ULL,      //g4
    1161999073681608712ULL,     //h4
    288793334762704928ULL,      //a3
    577868148797087808ULL,      //b3
    1227793891648880768ULL,     //c3
    2455587783297826816ULL,     //d3
    4911175566595588352ULL,     //e3
    9822351133174399489ULL,     //f3
    1197958188344280066ULL,     //g3
    2323857683139004420ULL,     //h3
    144117404414255168ULL,      //a2
    360293502378066048ULL,      //b2
    720587009051099136ULL,      //c2
    1441174018118909952ULL,     //d2
    2882348036221108224ULL,     //e2
    5764696068147249408ULL,     //f2
    11529391036782871041ULL,    //g2
    4611756524879479810ULL,     //h2
    567382630219904ULL,         //a1
    1416240237150208ULL,        //b1
    2833579985862656ULL,        //c1
    5667164249915392ULL,        //d1
    11334324221640704ULL,       //e1
    22667548931719168ULL,       //f1
    45053622886727936ULL,       //g1
    18049651735527937ULL,       //h1
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

//RADERA FUNKTION OM DU VILL -erik
u64 generate_bishop_attacks(){
    u64 empty = 0x0000000000000000;

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
    
    return 0ULL;
}

u64 get_bishop_attacks(int square, int currentSide){
    u64 newAttacks = 0ULL;
    int i = square - 9;
    while (i >= 0) {
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i -= 9;
    }
    i = square - 7;
    while ( i >= 0) {
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i -= 7;
    }
    i = square + 7;
    while ( i < 64) {
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i += 7;
    }
    i = square + 9;
    while ( i < 64) {
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i += 9;
    }
    newAttacks &= ~(occupancy[currentSide]) | occupancy[!currentSide];
    newAttacks &= bishopAttacks[square];
    return newAttacks;
}

u64 get_rook_attacks(int square, int currentSide){
    u64 newAttacks = 0ULL;
    int i = square - 1;
    while (i >= 0){
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i -= 1;
    }
    i = square - 8;
    while ( i >= 0) {
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i -= 8;
    }
    i = square + 8;
    while ( i < 64) {
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i += 8;
    }
    i = square + 1;
    while ( i < 64) {
        if( !get_bit(occupancy[both], i) )
            set_bit(newAttacks, i);
        else {
            set_bit(newAttacks, i);
            break;
        }
        i += 1;
    }
    newAttacks &= ~(occupancy[currentSide]) | occupancy[!currentSide];
    newAttacks &= rookAttacks[square];
    return newAttacks;
}

u64 get_queen_attacks(int square, int currentSide){
    u64 attacks = 0ULL;
    attacks |= get_bishop_attacks(square, currentSide);
    attacks |= get_rook_attacks(square, currentSide);
    return attacks;
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
    u64 ranks[8] = {a,b,c,d,e,f,g,h};

    u64 aa = 0x0101010101010101; // file a
    u64 bb = 0x0202020202020202; // file b
    u64 cc = 0x0404040404040404; // file c
    u64 dd = 0x0808080808080808; // file d
    u64 ee = 0x1010101010101010; // file e
    u64 ff = 0x2020202020202020; // file f
    u64 gg = 0x4040404040404040; // file g
    u64 hh = 0x8080808080808080; // file h
    u64 files[] = {aa,bb,cc,dd,ee,ff,gg,hh};

    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            int square = 8*i+j;
            std::cout << "square: " << squareToCoord[square] << std::endl;
            u64 result = ranks[i] | files[j];
            clear_bit(result, square);
            print_bitboard(result);
            getchar();
            // std::cout << result << "ULL," << std::endl;
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

// Lets say we want to see if square e4 is attacked.
// check all different pieces on the attacking side
// say attacking side is white. Then we just check the 
// attackTable for every square from the black side.
// If we find a white piece within these attacked squares
// we know that "because we can attack him, he can attack us"
// therefore square is attacked

// int side is the attacking side    // can speed this up by saving rook and bishop attacks for queen
bool square_attacked(int side, int square) {
    // Leaving them here if change is needed
    // u64 queenAttacks;
    // u64 rookAtks;
    // u64 bishopAtks;
    if (side == white) {
        // rookAtks = get_rook_attacks(square, black);
        // bishopAtks = get_bishop_attacks(square, black);
        // queenAttacks |= rookAtks | bishopAtks;
        if ( pawnAttacks[black][square] & bitboards[P] )         return true;
        if ( knightAttacks[square] & bitboards[N])               return true;
        if ( kingAttacks[square] & bitboards[K])                 return true;
        if ( get_rook_attacks(square, black) & bitboards[R])     return true;
        if ( get_bishop_attacks(square, black) & bitboards[B])   return true;
        if ( get_queen_attacks(square, black) & bitboards[Q])    return true; 
    } else {
        if ( pawnAttacks[white][square] & bitboards[p] )         return true;
        if ( knightAttacks[square] & bitboards[n])               return true;
        if ( kingAttacks[square] & bitboards[k])                 return true;
        if ( get_rook_attacks(square, white) & bitboards[r])     return true;
        if ( get_bishop_attacks(square, white) & bitboards[b])   return true;
        if ( get_queen_attacks(square, white) & bitboards[q])    return true; 
    }
    return false;
}

void print_attacked_squares(int side) {
    std::cout << "all squares attacked by " << ((side == white) ? "white" : "black") << std::endl;
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            int square = 8 * rank + file;
            std::cout << (square_attacked(side, square) ? "X " : ". ");
        }
        printf("\n");
    }
}