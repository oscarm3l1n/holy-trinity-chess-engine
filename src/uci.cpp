#include <ctype.h>
#include "bitboard.h"
// converts following string
// 1r2r2k/1p1n3R/p1qp2pB/6Pn/P1Pp/3B4/1P2PQ1K/5R2 b - - 0 1
// to pieces on the board, and sets castling and en passant square
// and side to play
// Starting fen: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -
int parse_fen(char* fen){
    
    char ch;
    int square = 0;
    char piece;
    int emptySquares = 0;

    while (1) {
        ch = *fen;
        if ( isalpha(ch) ) {
            piece = ch;
            set_bit(bitboards[piece], square);  
        }
        else if ( isdigit(ch) ) {
            emptySquares = ch - '0';
            square += emptySquares;
        }
        
        square++;
        fen++;
    }
}