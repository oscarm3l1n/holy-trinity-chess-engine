#include <iostream>
// #include "bitboard.h"
// #include "attack.cpp"
// #include "uci.cpp"
// #include "init.cpp"
#include "moves.cpp"

#define STARTFEN (char*)"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define RANDOM (char*)"r3k2r/pppppppp/1n1q4/2b1bn2/3NB3/1Q6/PPPPPPPP/R3K2R b KQkq - 0 1"
#define ENPAS (char*) "8/pp1ppppp/8/2pP4/8/8/8/8 w - c6 0 1"
#define TRICKY (char*) "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"

u64 nodes;
void perft_test(int depth){
    if (depth == 0){
        nodes++;
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


    parse_fen(TRICKY);

    // for(int i = 0; i < 5; i++){
    //     perft_test(i);
    //     std::cout << "nodes: " << nodes << std::endl;
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