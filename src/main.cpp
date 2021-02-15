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

int parse_move(std::string uciMove){
    std::vector<int> moveList;
    generate_legal_moves(moveList);

    int fromSq = (uciMove[0] - 'a') + (8 - (uciMove[1] - '0')) * 8;
    int toSq   = (uciMove[2] - 'a') + (8 - (uciMove[3] - '0')) * 8;

    int promotedPiece = 0;

    for (int i = 0; i < moveList.size(); i++){
        int move = moveList[i];

        if (fromSq == get_fromSq(move) && toSq == get_toSq(move)){

            promotedPiece = get_promotedPiece(move);
            if (promotedPiece){
                if ((promotedPiece == Q || promotedPiece == q) && uciMove[4] == 'q')
                    return move;
                else if((promotedPiece == R || promotedPiece == r) && uciMove[4] == 'r')
                    return move;
                else if((promotedPiece == N || promotedPiece == n) && uciMove[4] == 'n')
                    return move;
                else if((promotedPiece == B || promotedPiece == b) && uciMove[4] == 'b')
                    return move;
                else
                    continue;
            }

            // legal move
            return move;
        }
    }
    // illegal move
    return 0;
}

// the position command like in stockfish. for example, to set fen: positin fen *fen string*
void parse_position(char* command){
    // skip the "position word" by shifting pointer 9 steps
    command += 9;

    char *current = command;

    if (strncmp(command, "startpos", 8) == 0){
        parse_fen(STARTFEN);
    } else {
        current = strstr(command, "fen");

        if (current == NULL)
            parse_fen(STARTFEN);
        else {
            current += 4;
            parse_fen(current);
        }
    }
    current = strstr(command, "moves");

    if (current != NULL) {
        current += 6;

        while (*current) {
            int move = parse_move(current);

            if (move == 0)
                break;
            
            make_move(move, false);

            while (*current && *current != ' ') 
                current++;
            
            current++;
        }
    }

    print_board();
}

// "go" command
void parse_go(char *command){
    int depth = -1;

    if (strncmp(command, "go depth", 8) == 0){
        // if command is correct, skip the string part and go to the integer
        command += 9;

        depth = std::stoi(command);
        if (depth > 10)
            depth = 6;
    }
    else
        depth = 6;
    
    findMove(depth);
}

void uci_loop(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    char input[2000];

    printf("holy trinity chess engine\n");
    printf("uciok\n");

    while (1) {
        memset(input, 0, sizeof(input));

        fflush(stdout);

        if (!fgets(input, 2000, stdin))
            continue;
        
        else if (input[0] == '\n')
            continue;

        else if (strncmp(input, "isready", 7) == 0) 
            printf("readyok\n");

        else if (strncmp(input, "position", 8) == 0)
            parse_position(input);
        
        else if (strncmp(input, "ucinewgame", 10) == 0)
            parse_position((char*)"position startpos");
        
        else if (strncmp(input, "go", 2) == 0)
            parse_go(input);
        
        else if (strncmp(input, "quit", 4) == 0)
            break;

        else if (strncmp(input, "uci", 3) == 0){
            printf("holy trinity chess engine\n");
            printf("uciok\n");
        }
        else if (strncmp(input, "d", 1) == 0){
            print_board();
        }
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
            std::string playerMove;
            printf("make move\n > ");
            std::cin >> playerMove;
            int move = parse_move(playerMove);
            if (move)
                make_move(move, false);
            else
                printf("illegal move, try again\n");
        } else {
            findMove(1);
        }
    }

    return 0;
}