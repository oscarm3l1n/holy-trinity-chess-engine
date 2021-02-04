#include <iostream>
#include <vector>
// #include "bitboard.h"

void add_move(std::vector<int>& moveList, int move) {
    moveList.push_back(move);
}

// store the whole move in an integer i.e. 32 bits
// 00000000 00000000 00000000 00111111 fromSquare       6 bits
// 00000000 00000000 00001111 11000000 toSquare         6 bits ( >> 6)
// 00000000 00000000 11110000 00000000 piece            4 bits ( >> 12)
// 00000000 00001111 00000000 00000000 promotedPiece    4 bits ( >> 16)
// 00000000 00010000 00000000 00000000 captureFlag      1 bit  ( >> 20)
// 00000000 00100000 00000000 00000000 doubleMoveFlag    1 bit  ( >> 21)
// 00000000 01000000 00000000 00000000 enPassantFlag    1 bit  ( >> 22)
// 00000000 10000000 00000000 00000000 castlingFlag     1 bit  ( >> 23)

int encode_move(int fromSq, int toSq, int piece, int promotedPiece, int captureFlag, int doubleMoveFlag, int enPassantFlag, int castlingFlag) {
    int move = 0;
    move |= fromSq;
    move |= (toSq << 6);
    move |= (piece << 12);
    move |= (promotedPiece << 16);
    move |= (captureFlag << 20);
    move |= (doubleMoveFlag << 21);
    move |= (enPassantFlag << 22);
    move |= (castlingFlag << 23);
    return move;
}

void add_move(std::vector<int>& moveList, int move){
    moveList.push_back(move);
}