#include <iostream>
#include <vector>
#include "bitboard.h"
#include "attack.cpp"

#include "uci.cpp"
#include "init.cpp"

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

// #define get_fromSq(move)        (move & 0x3f)
// #define get_toSq(move)          ((move & 0xfc0) >> 6)
// #define get_piece(move)         ((move & 0xf000) >> 12)
// #define get_promotedPiece(move) ((move & 0xf0000) >> 16)
// #define get_captureFlag(move)   (move & 0x100000)
// #define get_doubleFlag(move) (move & 0x200000)
// #define get_enPassantFlag(move) (move & 0x400000)
// #define get_castlingFlag(move)  (move & 0x800000)
void print_moves(std::vector<int>& moveList){
    std::cout << "move      piece   promot      capt    doubl       EP      castl" << std::endl;
    for ( int i = 0; i < moveList.size(); i++){
        int move = moveList[i];
        std::cout << squareToCoord[get_fromSq(move)] <<
                     squareToCoord[get_toSq(move)]   << "       " << 
                     asciiPieces[get_piece(move)]    << "        " <<
                     (get_promotedPiece(move) ? asciiPieces[get_promotedPiece(move)] : 0) <<"         "<<
                     get_captureFlag(move)          << "         " <<
                     get_doubleFlag(move)           << "          " <<
                     get_enPassantFlag(move)        << "          " <<
                     get_castlingFlag(move)         << "          " << std::endl;
    }
}

// start generating all quiet moves
// which means the moves where no captures
// are made
// encode_move (from, to, piece, promPiece, capture, double, EP, castling)
void generate_moves(std::vector<int>& moveList) {
    int fromSq;
    int toSq;
    int move;
    u64 tempBitboard;
    u64 tempAttacks;

    for (int piece = P; piece <= k; piece++) {
        tempBitboard = bitboards[piece];

        if (side == white){
            if (piece == P){
                while(tempBitboard){
                    fromSq = get_index(tempBitboard);
                    toSq = fromSq - 8;

                    // Pawn quiet moves
                    // check if the square is empty
                    if ( (toSq > 0) && !get_bit(occupancy[both], toSq)){
                        // pawn promotion
                        if ( fromSq >= a7 && fromSq <= h7){
                            add_move(moveList, encode_move(fromSq, toSq, P, Q, 0, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, P, N, 0, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, P, B, 0, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, P, R, 0, 0, 0, 0));
                        } else {
                            // one square forward                    
                            add_move(moveList, encode_move(fromSq, toSq, P, 0, 0, 0, 0, 0));
                            // two squares forward
                            if ( (fromSq >= a2 && fromSq <= h2) && !get_bit(occupancy[both], toSq - 8)){
                                add_move(moveList, encode_move(fromSq, toSq - 8, P, 0, 0, 1, 1, 0));
                            }
                        }
                    }
                    // Pawn capture moves
                    tempAttacks = pawnAttacks[white][fromSq] & occupancy[black];
                    while(tempAttacks) {
                        toSq = get_index(tempAttacks);

                        // promotion
                        if ( fromSq >= a7 && fromSq <= h7){
                            add_move(moveList, encode_move(fromSq, toSq, P, Q, 1, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, P, N, 1, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, P, B, 1, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, P, R, 1, 0, 0, 0));
                        } else {
                            // normal capture
                            add_move(moveList, encode_move(fromSq, toSq, P, 0, 1, 0, 0, 0));
                        }
                        clear_bit(tempAttacks, toSq);
                    }
                    // En passant
                    if (enPassant != noSquare) {
                        if (pawnAttacks[white][fromSq] & (1ULL << enPassant)){
                            // int targetSq = get_index(enPassAttack);
                            add_move(moveList, encode_move(fromSq, enPassant, P, 0, 1, 0, 0, 0));
                        }
                    }
                    clear_bit(tempBitboard, fromSq);
                }
            }
            // Castling moves
            if (piece == K) {
                if (castlingRights & wk){
                    // Check so squares are not blocked
                    if (!get_bit(occupancy[both], f1) && !get_bit(occupancy[both], g1)){
                        // Check so squares are not attacked
                        if (!square_attacked(black, f1) && !square_attacked(black, g1)){
                            // castle king side
                            add_move(moveList, encode_move(e1, g1, K, 0, 0, 0, 0, 1));
                        }
                    }
                }
                if (castlingRights & wq){
                    if (!get_bit(occupancy[both], d1) && !get_bit(occupancy[both], c1) && !get_bit(occupancy[both], b1)){
                        if(!square_attacked(black, d1) && !square_attacked(black, c1)){
                            add_move(moveList, encode_move(e1, c1, K, 0, 0, 0, 0, 1));
                        }
                    }
                }
            }
        } else {
            // black pawn and king moves
            if (piece == p){
                while(tempBitboard){
                    fromSq = get_index(tempBitboard);
                    toSq = fromSq + 8;

                    // Pawn quiet moves
                    // check if the square is empty
                    if ( (toSq < 64) && !get_bit(occupancy[both], toSq)){
                        // pawn promotion
                        if ( fromSq >= a2 && fromSq <= h2){
                            add_move(moveList, encode_move(fromSq, toSq, p, q, 0, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, p, n, 0, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, p, b, 0, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, p, r, 0, 0, 0, 0));
                        } else {
                            // one square forward                    
                            add_move(moveList, encode_move(fromSq, toSq, p, 0, 0, 0, 0, 0));
                            
                            // two squares forward
                            if ( (fromSq >= a7 && fromSq <= h7) && !get_bit(occupancy[both], toSq + 8)){
                                add_move(moveList, encode_move(fromSq, toSq + 8, p, 0, 0, 1, 1, 0));
                            }
                        }
                    }
                    // Pawn capture moves
                    tempAttacks = pawnAttacks[black][fromSq] & occupancy[white];
                    while(tempAttacks) {
                        toSq = get_index(tempAttacks);

                        // promotion
                        if ( fromSq >= a2 && fromSq <= h2){
                            add_move(moveList, encode_move(fromSq, toSq, p, q, 1, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, p, b, 1, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, p, r, 1, 0, 0, 0));
                            add_move(moveList, encode_move(fromSq, toSq, p, n, 1, 0, 0, 0));
                        } else {
                            // normal capture
                            add_move(moveList, encode_move(fromSq, toSq, p, 0, 1, 0, 0, 0));
                        }
                        clear_bit(tempAttacks, toSq);
                    }
                    // En passant
                    if (enPassant != noSquare) {
                        if (pawnAttacks[black][fromSq] & (1ULL << enPassant)){
                            // int targetSq = get_index(enPassAttack);
                            add_move(moveList, encode_move(fromSq, enPassant, p, 0, 1, 0, 0, 0));
                        }
                    }
                    clear_bit(tempBitboard, fromSq);
                }
            }
            // Castling moves
            if (piece == k) {
                if (castlingRights & bk){
                    // Check so squares are not blocked
                    if (!get_bit(occupancy[both], f8) && !get_bit(occupancy[both], g8)){
                        // Check so squares are not attacked
                        if (!square_attacked(white, f8) && !square_attacked(white, g8)){
                            // castle king side
                            add_move(moveList, encode_move(e8, g8, k, 0, 0, 0, 0, 1));
                        }
                    }
                }
                if (castlingRights & bq){
                    if (!get_bit(occupancy[both], d8) && !get_bit(occupancy[both], c8) && !get_bit(occupancy[both], b8)){
                        if(!square_attacked(white, d8) && !square_attacked(white, c8)){
                            add_move(moveList, encode_move(e8, c8, k, 0, 0, 0, 0, 1));
                        }
                    }
                }
            }
        }

        // Rooks
        if ((side == white) ? piece == R : piece == r) {
            while(tempBitboard) {
                fromSq = get_index(tempBitboard);
                tempAttacks = get_rook_attacks(fromSq, side);
                while (tempAttacks){
                    toSq = get_index(tempAttacks);
                    if (get_bit(tempAttacks, toSq) && get_bit(occupancy[!side], toSq)){
                        // capture move
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 1, 0, 0, 0));
                    } else {
                        // quiet
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 0, 0, 0, 0));
                    }
                    clear_bit(tempAttacks, toSq);
                }
                clear_bit(tempBitboard, fromSq);
            }
        }
        // Bishops
        if ((side == white) ? piece == B : piece == b) {
            while(tempBitboard) {
                fromSq = get_index(tempBitboard);
                tempAttacks = get_bishop_attacks(fromSq, side);
                while (tempAttacks){
                    toSq = get_index(tempAttacks);
                    if (get_bit(tempAttacks, toSq) && get_bit(occupancy[!side], toSq)){
                        // capture move
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 1, 0, 0, 0));
                    } else {
                        // quiet
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 0, 0, 0, 0));
                    }
                    clear_bit(tempAttacks, toSq);
                }
                clear_bit(tempBitboard, fromSq);
            }
        }
        // Knights
        if ((side == white) ? piece == N : piece == n){
            while (tempBitboard){   
                fromSq = get_index(tempBitboard);
                tempAttacks = knightAttacks[fromSq];
                while (tempAttacks){
                    toSq = get_index(tempAttacks);
                    if (get_bit(tempAttacks, toSq) && get_bit(occupancy[!side], toSq)){
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 1, 0, 0, 0));
                    } else if (get_bit(tempAttacks, toSq) && !get_bit(occupancy[side], toSq)){
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 0, 0, 0, 0));
                    }
                    clear_bit(tempAttacks, toSq);
                }

                clear_bit(tempBitboard, fromSq);
            }
        }

        // Queens
        if ((side == white) ? piece == Q : piece == q) {
            while(tempBitboard) {
                fromSq = get_index(tempBitboard);
                tempAttacks = get_bishop_attacks(fromSq, side);
                tempAttacks |= get_rook_attacks(fromSq, side);
                while (tempAttacks){
                    toSq = get_index(tempAttacks);
                    if (get_bit(tempAttacks, toSq) && get_bit(occupancy[!side], toSq)){
                        // capture move
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 1, 0, 0, 0));
                    } else {
                        // quiet
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 0, 0, 0, 0));
                    }
                    clear_bit(tempAttacks, toSq);
                }
                clear_bit(tempBitboard, fromSq);
            }
        }
        // Kings
        if ((side == white) ? piece == K : piece == k){
            while (tempBitboard){   
                fromSq = get_index(tempBitboard);
                tempAttacks = kingAttacks[fromSq];
                while (tempAttacks){
                    toSq = get_index(tempAttacks);
                    if (get_bit(tempAttacks, toSq) && get_bit(occupancy[!side], toSq)){
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 1, 0, 0, 0));
                    } 
                    else if (get_bit(tempAttacks, toSq) && !get_bit(occupancy[side], toSq)) {
                        add_move(moveList, encode_move(fromSq, toSq, piece, 0, 0, 0, 0, 0));
                    }
                    clear_bit(tempAttacks, toSq);
                }

                clear_bit(tempBitboard, fromSq);
            }
        }
    }
}


const int castling_rights[64] = {
     7, 15, 15, 15,  3, 15, 15, 11,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    13, 15, 15, 15, 12, 15, 15, 14
};


// fromSq, toSq, piece, promotedPiece, captureFlag, doubleMoveFlag, enPassantFlag, castlingFlag
bool make_move(int move, bool captureMovesOnly){
    int from        = get_fromSq(move);
    int to          = get_toSq(move);
    int piece       = get_piece(move);
    int promoted    = get_promotedPiece(move);
    int capture     = get_captureFlag(move);
    int doublePush  = get_doubleFlag(move);
    int enPas       = get_enPassantFlag(move);
    int castle      = get_castlingFlag(move);

    save_board();

    if (!captureMovesOnly){
        // make move
        clear_bit(bitboards[piece], from);
        set_bit(bitboards[piece], to);

        // find the captured piece and pop it
        if (side == white){
            for(int i = p; i <= k; i++){
                if (get_bit(bitboards[i], to)){
                    clear_bit(bitboards[i], to);
                    break;
                }
            }
        } else {
            for(int i = P; i <= K; i++){
                if (get_bit(bitboards[i], to)){
                    clear_bit(bitboards[i], to);
                    break;
                }
            }
        }

        // handle en passant
        if (enPas){
            if (side == white){
                clear_bit(bitboards[p], to + 8);
            } else {
                clear_bit(bitboards[P], to - 8);
            }
        }
        enPassant = noSquare;

        // handle double push
        if (doublePush) {
            if (side == white){
                enPassant = to + 8;
            } else {
                enPassant = to - 8;
            }
        }

        // handle castling
        if (castle) {
            switch (to){
            case g1:
                clear_bit(bitboards[R], h1);
                set_bit(bitboards[R], f1);
                clear_bit(bitboards[K], e1);
                set_bit(bitboards[K], g1);
                break;
            case c1:
                clear_bit(bitboards[R], a1);
                set_bit(bitboards[R], d1);
                clear_bit(bitboards[K], e1);
                set_bit(bitboards[K], c1);
                break;
            case g8:
                clear_bit(bitboards[r], h8);
                set_bit(bitboards[r], f8);
                clear_bit(bitboards[k], e8);
                set_bit(bitboards[k], g8);
                break;
            case c8:
                clear_bit(bitboards[r], a8);
                set_bit(bitboards[r], d8);
                clear_bit(bitboards[k], e8);
                set_bit(bitboards[k], c8);
                break;
            }
        }

        // handle promotion
        if (promoted) {
            if (side == white){
                clear_bit(bitboards[P], to);
                set_bit(bitboards[promoted], to);
            } else {
                clear_bit(bitboards[p], to);
                set_bit(bitboards[promoted], to);
            }
        }

        // update castling rights
        castlingRights &= castling_rights[from];
        castlingRights &= castling_rights[to];

        memset(occupancy, 0ULL, sizeof(occupancy));

        // set occupancy
        for(int i = P; i <= K; i++)
            occupancy[white] |= bitboards[i];
        for(int i = p; i <= k; i++)
            occupancy[black] |= bitboards[i];

        occupancy[both] |= occupancy[white];
        occupancy[both] |= occupancy[black];

        
        // check so king is not in check
        
        bool illegalMove;
        int kingSq = (side == white) ? get_index(bitboards[K]) : get_index(bitboards[k]);
        illegalMove = square_attacked(!side, kingSq);

        side ^= 1;

        if (illegalMove){
            // restore board and return illegal move
            restore_board();
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}