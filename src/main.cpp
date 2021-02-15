#include <iostream>
// #include "bitboard.h"
// #include "attack.cpp"
// #include "uci.cpp"
// #include "init.cpp"
#include "moves.cpp"

#define STARTFEN (char*) "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define RANDOM (char*)"r3k2r/pppppppp/1n1q4/2b1bn2/3NB3/1Q6/PPPPPPPP/R3K2R b KQkq - 0 1"
#define ENPAS (char*) "8/pp1ppppp/8/2pP4/8/8/8/8 w - c6 0 1"
#define TRICKY (char*) "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -  "
#define TRICKY2 (char*) "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1b2P3/5Q1p/PPPBBPPP/R3K2R w KQkq - "
#define POS3 (char*) "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - "
#define POS4 (char*) "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"
#define POS5 (char*) "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  "


int perft_test(int depth){
    if (depth == 0){
        return 1;
    }
    std::vector<int> ml;
    generate_legal_moves(ml);
    int num_positions = 0;

    for (int i = 0; i < ml.size(); i++){
        save_board();
        if (!make_move(ml[i], false))
            continue;
        num_positions += perft_test(depth-1);
        restore_board();
    }
    return num_positions;
}


void test(int depth){
    if (depth == 0){
        return;
    }
    std::vector<int> ml;
    generate_legal_moves(ml);

    print_board();
    getchar();

    for (int i = 0; i < ml.size(); i++){
        save_board();
        if (!make_move(ml[i], false))
            continue;
        print_board();
        getchar();
        test(depth-1);
        restore_board();
    }
}


// https://lichess.org/editor
// to create custom FEN's

int main(){
    init();
    init_leaper_attacks();

    parse_fen(STARTFEN);

    while (1){
        print_board();
        if (side){

            std::cout << "eval: " << evaluate() << std::endl;

            std::cout << "player move\n > ";

            std::string playerMove;
            std::cin >> playerMove; 

            int move = make_player_move(playerMove);

            if (move){
                make_move(move, false);
            } else {
                std::cout << "illegal move" << std::endl;
            }
        } else {
            findMove(4);
        }
    }

    return 0;
}