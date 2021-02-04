#include <iostream>
// #include "bitboard.h"
// #include "attack.cpp"
// #include "uci.cpp"
// #include "init.cpp"
#include "moves.cpp"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define FOR(n) for(int i = 0; i < n; i++)

// https://lichess.org/editor
// to create custom FEN's
int main(){
    init();
    init_leaper_attacks();


    parse_fen( (char*) STARTFEN);
    std::vector<int> moveList;
    generate_moves(moveList);

    for(int i = 0; i < moveList.size(); i++){

        int move = moveList[i];
        save_board();
        if (!make_move(move, false))
            continue;
        print_board();
        getchar();
        restore_board();
        print_board();
        getchar();

    }


    return 0;
}