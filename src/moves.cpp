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

void print_move(std::string type, int fromSq, int toSq){
    std::cout << squareToCoord[fromSq] << squareToCoord[toSq] << " " << type << " " << std::endl;
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
                            // add_move(moveList, encode_move(fromSq, toSq, P, Q, 0, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, N, 0, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, B, 0, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, R, 0, 0, 0, 0));
                            print_move("normal promotion Q", fromSq, toSq);
                            print_move("normal promotion N", fromSq, toSq);
                            print_move("normal promotion B", fromSq, toSq);
                            print_move("normal promotion R", fromSq, toSq);
                        } else {
                            // one square forward                    
                            // add_move(moveList, encode_move(fromSq, toSq, P, 0, 0, 0, 0, 0));
                            print_move("one square forward", fromSq, toSq);
                            // two squares forward
                            if ( (fromSq >= a2 && fromSq <= h2) && !get_bit(occupancy[both], toSq - 8)){
                                // add_move(moveList, encode_move(fromSq, toSq-8, P, 0, 0, 1, 1, 0));
                                print_move("two squares forward", fromSq, toSq-8);
                            }
                        }
                    }
                    // Pawn capture moves
                    tempAttacks = pawnAttacks[white][fromSq] & occupancy[black];
                    while(tempAttacks) {
                        toSq = get_index(tempAttacks);

                        // promotion
                        if ( fromSq >= a7 && fromSq <= h7){
                            // add_move(moveList, encode_move(fromSq, toSq, P, Q, 1, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, N, 1, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, B, 1, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, R, 1, 0, 0, 0));
                            print_move("capture promotion Q", fromSq, toSq);
                            print_move("capture promotion N", fromSq, toSq);
                            print_move("capture promotion B", fromSq, toSq);
                            print_move("capture promotion R", fromSq, toSq);
                            
                        } else {
                            // normal capture
                            // add_move(moveList, encode_move(fromSq, toSq, P, 0, 1, 0, 0, 0));
                            print_move("capture move", fromSq, toSq);
                        }
                        clear_bit(tempAttacks, toSq);
                    }
                    // En passant
                    if (enPassant != noSquare) {
                        if (pawnAttacks[white][fromSq] & (1ULL << enPassant)){
                            // int targetSq = get_index(enPassAttack);
                            // add move
                            print_move("En passant", fromSq, enPassant);
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
                            print_move("Castle kingside", e1, g1);
                        }
                    }
                }
                if (castlingRights & wq){
                    if (!get_bit(occupancy[both], d1) && !get_bit(occupancy[both], c1) && !get_bit(occupancy[both], b1)){
                        if(!square_attacked(black, d1) && !square_attacked(black, c1)){
                            print_move("Castle queenside",e1,c1);
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
                            // add_move(moveList, encode_move(fromSq, toSq, P, Q, 0, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, N, 0, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, B, 0, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, R, 0, 0, 0, 0));
                            print_move("normal promotion Q", fromSq, toSq);
                            print_move("normal promotion N", fromSq, toSq);
                            print_move("normal promotion B", fromSq, toSq);
                            print_move("normal promotion R", fromSq, toSq);
                        } else {
                            // one square forward                    
                            // add_move(moveList, encode_move(fromSq, toSq, P, 0, 0, 0, 0, 0));
                            print_move("one square forward", fromSq, toSq);
                            // two squares forward
                            if ( (fromSq >= a7 && fromSq <= h7) && !get_bit(occupancy[both], toSq + 8)){
                                // add_move(moveList, encode_move(fromSq, toSq-8, P, 0, 0, 1, 1, 0));
                                print_move("two squares forward", fromSq, toSq + 8);
                            }
                        }
                    }
                    // Pawn capture moves
                    tempAttacks = pawnAttacks[black][fromSq] & occupancy[white];
                    while(tempAttacks) {
                        toSq = get_index(tempAttacks);

                        // promotion
                        if ( fromSq >= a2 && fromSq <= h2){
                            // add_move(moveList, encode_move(fromSq, toSq, P, Q, 1, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, N, 1, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, B, 1, 0, 0, 0));
                            // add_move(moveList, encode_move(fromSq, toSq, P, R, 1, 0, 0, 0));
                            print_move("capture promotion Q", fromSq, toSq);
                            print_move("capture promotion N", fromSq, toSq);
                            print_move("capture promotion B", fromSq, toSq);
                            print_move("capture promotion R", fromSq, toSq);
                            
                        } else {
                            // normal capture
                            // add_move(moveList, encode_move(fromSq, toSq, P, 0, 1, 0, 0, 0));
                            print_move("capture move", fromSq, toSq);
                        }
                        clear_bit(tempAttacks, toSq);
                    }
                    // En passant
                    if (enPassant != noSquare) {
                        if (pawnAttacks[black][fromSq] & (1ULL << enPassant)){
                            // int targetSq = get_index(enPassAttack);
                            // add move
                            print_move("En passant", fromSq, enPassant);
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
                            print_move("Castle kingside", e8, g8);
                        }
                    }
                }
                if (castlingRights & bq){
                    if (!get_bit(occupancy[both], d8) && !get_bit(occupancy[both], c8) && !get_bit(occupancy[both], b8)){
                        if(!square_attacked(white, d8) && !square_attacked(white, c8)){
                            print_move("Castle queenside",e8,c8);
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
                        print_move("capture",fromSq, toSq);
                    } else {
                        // quiet
                        print_move("",fromSq, toSq);
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
                        print_move("capture",fromSq, toSq);
                    } else {
                        // quiet
                        print_move("",fromSq, toSq);
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
                        print_move("capture",fromSq,toSq);
                    } else {
                        print_move("",fromSq,toSq);
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
                        print_move("capture",fromSq, toSq);
                    } else {
                        // quiet
                        print_move("",fromSq, toSq);
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
                        print_move("capture",fromSq,toSq);
                    } else {
                        print_move("",fromSq,toSq);
                    }
                    clear_bit(tempAttacks, toSq);
                }

                clear_bit(tempBitboard, fromSq);
            }
        }
    }
}