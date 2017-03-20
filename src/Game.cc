#include "Game.h"

Game::Game() {
    board = Board();
    board.drawBoard();
    maxDepth = 7;
}

int Game::colToInt(char col) {
    switch (col) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        default:  return -1;
    }
}

char Game::colToChar(int col) {
    return "ABCDEF"[col];
}

int Game::decodeSpace(std::string space) {
    char x = space.at(0);
    char y = space.at(1);

    int xInt = colToInt(x);
    int yInt = y - '0' - 1;
    
    return (yInt * 6) + xInt;
}

std::string Game::encodeSpace(int space) {
    int x = space % 6;
    int y = space / 6 + 1;

    std::stringstream result;
    result << "ABCDEF"[x];
    result << y;
    return result.str();
}

void Game::inputMove() {
    std::cout << "---- All Legal Moves ----\n";
    std::vector<int> moves = board.getHumanMoves();
    if (moves.size() == 0) {
        gameEnd(false);
    }
    for (size_t i = 0; i < moves.size(); i+= 2) {
        std::cout << encodeSpace(moves[i]) << encodeSpace(moves[i+1]) << "\n";
    }
    std::cout << "\n";

    bool legal = false;
    std::string in;
    int from;
    int to;

    do {
        std::cout << "Enter your move: ";
        std::cin >> in;
        from = decodeSpace(in.substr(0,2));
        to = decodeSpace(in.substr(2,2));

        for (size_t i = 0; i < moves.size(); i+= 2) {
            if (moves[i] == from) {
                if (moves[i+1] == to) {
                    legal = true;
                    i = moves.size();
                }
            }
        }
        if (!legal) {
            std::cout << in << " is not a legal move. Please use one of the indicated legal moves.\n";
        }
    } while (!legal);
    std::cout << "\n";

    board.makeMove(from, to);
    board.drawBoard();
}

void Game::makeComputerMove() {
    std::cout << "Here I goooooooo\n";
    std::vector<int> moves = board.getComputerMoves();
    if (moves.size() == 0) gameEnd(1);

    int bestScore = -9999, depth = 0, curScore, bestFrom, fromPiece, toPiece;
    size_t i;
    for (i = 0; i < moves.size(); i+= 2) {
        std::cout << "Evaluating " << encodeSpace(moves[i]) << encodeSpace(moves[i+1]) << "...\n";
        fromPiece = board.getPieceAt(moves[i]);
        toPiece = board.getPieceAt(moves[i+1]);
        board.makeMove(moves[i], moves[i+1]);
        curScore = min(depth + 1, bestScore);
        if (curScore > bestScore) {
            bestFrom = i;
            bestScore = curScore;
        }
        board.undoMove(moves[i], fromPiece, moves[i+1], toPiece);
    }
    std::cout << "\nMy move is " << encodeSpace(moves[bestFrom]) << encodeSpace(moves[bestFrom + 1]) << "\n\n";
    board.makeMove(moves[bestFrom], moves[bestFrom+1]);
    board.drawBoard();
    std::cout << "\n";
}

int Game::min(int depth, int alpha) {
    int bestScore = 20000, curScore, fromPiece, toPiece;
    int kingStatus = board.checkBothKings();
    if (depth == maxDepth) return evaluate();
    if (kingStatus != 0) return (kingStatus * 10000);
    std::vector<int> moves = board.getHumanMoves();

    if (moves.size() == 0)  return 10000;

    size_t i;
    for (i = 0; i < moves.size(); i+=2) {
        fromPiece = board.getPieceAt(moves[i]);
        toPiece = board.getPieceAt(moves[i+1]);
        board.makeMove(moves[i], moves[i+1]);
        curScore = max(depth + 1, bestScore);
        if (curScore < bestScore) {
            bestScore = curScore;
        }
        board.undoMove(moves[i], fromPiece, moves[i+1], toPiece);
        if (bestScore <= alpha) {
            std::vector<int>().swap(moves);
            return bestScore;
        }
    }

    std::vector<int>().swap(moves);
    return bestScore;
}

int Game::max(int depth, int beta) {
    int bestScore = -20000, curScore, fromPiece, toPiece;
    int kingStatus = board.checkBothKings();
    if (depth == maxDepth) return evaluate();
    if (kingStatus != 0) return (kingStatus * 10000);
    std::vector<int> moves = board.getComputerMoves();

    if (moves.size() == 0)  return -10000;

    size_t i;
    for (i = 0; i < moves.size(); i+=2) {
        fromPiece = board.getPieceAt(moves[i]);
        toPiece = board.getPieceAt(moves[i+1]);
        board.makeMove(moves[i], moves[i+1]);
        curScore = min(depth + 1, bestScore);
        if (curScore > bestScore) {
            bestScore = curScore;
        }
        board.undoMove(moves[i], fromPiece, moves[i+1], toPiece);
        if (bestScore >= beta) {
            std::vector<int>().swap(moves);
            return bestScore;
        }
    }
    std::vector<int>().swap(moves);
    return bestScore;
}

int Game::evaluate() {
    return 1;
}

void Game::checkForGameEnd() {
    int endStatus = board.checkBothKings();
    if (endStatus != 0) {
        gameEnd(endStatus);
    }
}

void Game::gameEnd(bool humanWins) {
    if (humanWins) {
        std::cout << "Congratulations, you win!\n";
        exit(0);
    } else {
        std::cout << "Sorry, you lise!\n";
        exit(0);
    }
}
