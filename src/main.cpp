#include <iostream>
// #include "bitboard.h"
// #include "attack.cpp"
// #include "uci.cpp"
// #include "init.cpp"
#include "moves.cpp"

#define STARTFEN (char*)"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define RANDOM (char*)"r3k2r/pppppppp/1n1q4/2b1bn2/3NB3/1Q6/PPPPPPPP/R3K2R b KQkq - 0 1"
#define ENPAS (char*) "8/pp1ppppp/8/2pP4/8/8/8/8 w - c6 0 1"
#define TRICKY (char*) "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -  "
#define TRICKY2 (char*) "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1b2P3/5Q1p/PPPBBPPP/R3K2R w KQkq - "
#define POS3 (char*) "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - "
#define POS4 (char*) "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"
#define POS5 (char*) "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  "


u64 perft_nodes;
void perft_test(int depth){
    if (depth == 0){
        perft_nodes++;
        return;
    }
    std::vector<int> ml;
    generate_moves(ml);

    for(int i = 0; i < ml.size(); i++){
        save_board();
        if (!make_move(ml[i], false))
            continue;
        perft_test(depth-1);
        restore_board();
    }
}


// https://lichess.org/editor
// to create custom FEN's
int main(){
    init();
    init_leaper_attacks();

    init_slider_attacks(0);
    init_slider_attacks(1);


    parse_fen(TRICKY);

    // for(int i = 0; i < 6; i++){
    //     perft_test(i);
    //     std::cout << "nodes: " << perft_nodes << std::endl;
    //     nodes = 0;
    // }

    std::vector<int> ml;
    generate_moves(ml);

    for(int i = 0; i < ml.size(); i++){
        save_board();
        print_board();
        if(!make_move(ml[i],false))
            continue;
        getchar();
        print_board();
        restore_board();
        getchar();
    }


    return 0;
}