#include <ctype.h>
#include <cstring>
#include "bitboard.h"
// converts following string
// 1r2r2k/1p1n3R/p1qp2pB/6Pn/P1Pp/3B4/1P2PQ1K/5R2 b - - 0 1
// to pieces on the board, and sets castling and en passant square
// and side to play
// Starting fen: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -
void parse_fen(char* fen){

    memset(bitboards, 0ULL, sizeof(bitboards));
    memset(occupancy, 0ULL, sizeof(occupancy));
    
    int square = 0;
    int piece;
    int emptySquares = 0;

    while (*fen != ' ') {

        if ( isalpha(*fen) ) {
            piece = char_pieces[*fen];
            set_bit(bitboards[piece], square);  
            square++;
        }
        else if ( isdigit(*fen) ) {
            emptySquares = *fen - '0';
            square += emptySquares;
        }

        fen++;
    }
    fen++;

    side = (*fen == 'w') ? white : black;

    // go to castling rights
    fen += 2;

    while (*fen != ' ') {
        switch (*fen) {
            case 'K': castlingRights |= wk; break;
            case 'Q': castlingRights |= wq; break;
            case 'k': castlingRights |= bk; break;
            case 'q': castlingRights |= bq; break;
            case '-': break;
        }
        fen++;
    }
    fen++;

    if (*fen != '-'){
        int file = fen[0] - 'a';
        int rank = 8 - (fen[1] - '0');
        enPassant = 8 * rank + file;
    } else {
        enPassant = noSquare;
    }

    for (int piece = P; piece <= K; piece++) {
        occupancy[white] |= bitboards[piece];
    }
    for (int piece = p; piece <= k; piece++) {
        occupancy[black] |= bitboards[piece];
    }
    
    occupancy[both] |= occupancy[white];
    occupancy[both] |= occupancy[black];
}