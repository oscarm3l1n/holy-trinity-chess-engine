#pragma once

#include <string>
#include <unordered_map>

// Also contains macros

#define u64 unsigned long long

enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, noSquare
};

std::string squareToCoord[65] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "noSquare"
};

// Game variables

// pieces
enum {P,B,N,Q,R,K,p,b,n,q,r,k,noPiece};
std::unordered_map<int, char> char_pieces = {
    {'P', P},
    {'N', N},
    {'B', B},
    {'Q', Q},
    {'R', R},
    {'K', K},
    {'p', p},
    {'n', n},
    {'q', q},
    {'r', r},
    {'k', k},
    {'b', b}
};
std::string asciiPieces = "PBNQRKpbnqrk";


// colours
enum {black, white, both};

// castling rights
enum {wk = 1, wq = 2, bk = 4, bq = 8};

int enPassant; // Should be noSquare as default
int side; // black or white
int castlingRights;


u64 bitboards[12];  // for all pieces
u64 occupancy[3];   // white, black, both