import chess

board = chess.Board()
board.set_fen("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  ")

move = chess.Move.from_uci("a2a3")
board.push(move)
for move in board.legal_moves:
    board.push(move)
    for newmove in board.legal_moves:
        print(move, end=", ")
        print(newmove)
    board.pop()