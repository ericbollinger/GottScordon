#include "Game.h"

Game::Game() {
    board = Board();
    board.drawBoard();
    maxDepth = 0;
}

// Convert column letter to internal column number
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

// Convert internal column number to column letter
char Game::colToChar(int col) {
    if (col > 5) return -1;
    return "ABCDEF"[col];
}

// Convert string representation of board space (i.e. F6) to the respective
// internal board position number (i.e. 35)
int Game::decodeSpace(std::string space) {
    char x = space.at(0);
    char y = space.at(1);

    int xInt = colToInt(x);
    int yInt = y - '0' - 1;
    
    return (yInt * 6) + xInt;
}

// Convert internal representation of board space (i.e. 16) to the respective
// string used in move notation (i.e. E3)
std::string Game::encodeSpace(int space) {
    int x = space % 6;
    int y = space / 6 + 1;

    std::stringstream result;
    result << "ABCDEF"[x];
    result << y;
    return result.str();
}

std::string Game::reverseMove(Move move) {
    int from = move.getFrom();
    int to = move.getTo();

    std::stringstream result;
    result << "ABCDEF"[5 - (from % 6)];
    result << 8 - (from / 6);
    result << "ABCDEF"[5 - (to % 6)];
    result << 8 - (to / 6);
    return result.str();
}

// Take in user input to make player move
void Game::inputMove() {
    // Retrieve, print out legal moves that can be executed
    std::cout << "---- All Legal Moves ----\n";
    std::vector<Move> moves = board.getHumanMoves();
    
    // If there are no legal moves, you lose!
    if (moves.size() == 0) {
        gameEnd(false);
    }
    for (size_t i = 0; i < moves.size(); i++) {
        std::cout << encodeSpace(moves[i].getFrom()) << encodeSpace(moves[i].getTo());
        if (i <moves.size()-1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n\n";

    bool legal = false;
    std::string in;
    int from;
    int to;

    do {
        std::cout << "Enter your move: ";
        std::cin >> in;
        if (in.length() == 4) {
            from = decodeSpace(in.substr(0,2));
            to = decodeSpace(in.substr(2,2));

            for (size_t i = 0; i < moves.size(); i++) {
                if (moves[i].getFrom() == from) {
                    if (moves[i].getTo() == to) {
                        legal = true;
                        i = moves.size();
                    }
                }
            }
        }
        // Repeat process until a legal move is entered
        if (!legal) {
            std::cout << in << " is not a legal move. Please use one of the indicated legal moves.\n";
        }
    } while (!legal);
    std::cout << "\n";

    // Make selected move, print out new board state
    board.makeMove(Move(from,board.getPieceAt(from),to,board.getPieceAt(to),(board.getPieceAt(to)<0)));
    board.drawBoard();
}

// For iterative deepening. Set max depth back to the minimum
void Game::resetMaxDepth() {
    maxDepth = 0;
}

// For iterative deepening. Increase max depth to look deeper in the next iteration
void Game::increaseMaxDepth() {
    maxDepth++;
}

// See if 5 seconds have passed. If so, return true and OH JEEZ HURRY UP
bool Game::endTurnNow() {
    return time(NULL) >= turnEnd;
}

// Calculate and execute the best possible move for the computer player
void Game::makeComputerMove() {
    std::cout << "Evaluating possibilities...\n\n\n";
    turnEnd = time(NULL) + 5;

    // Get all legal moves for the computer player
    std::vector<Move> moves = board.getComputerMoves();
    std::sort(moves.begin(), moves.end());

    // If there are no legal moves, the computer player loses!
    if (moves.size() == 0) gameEnd(1);

    int lastIterationFrom, bestScore = -999999, depth, curScore, bestFrom = 0;
    
    // Iterative deepening loop. maxDepth effectively starts at 1, and is incremented each time
    do {
        depth = 0;

        lastIterationFrom = bestFrom;

        bestScore = -999999;
        increaseMaxDepth();
        //std::cout << "------ max ply: " << maxDepth << " -------\n";

        // For each possible move, record the pieces in each position, make the move,
        // calculate the minimax result for that move, and then undo the move
        for (size_t i = 0; i < moves.size(); i++) {
            board.makeMove(moves[i]);
            curScore = min(depth + 1, bestScore);
            //std::cout << "Score for  " << encodeSpace(moves[i].getFrom()) << encodeSpace(moves[i].getTo()) << ": " << curScore << "\n";
            if (curScore > bestScore) {
                bestFrom = i;
                bestScore = curScore;
            }
            board.undoMove(moves[i]);
            
            // if it's been five seconds since the turn started, OH GOD HURRY UP
            if (endTurnNow()) i = moves.size();
        }


    } while (!endTurnNow());
    std::cout << "Selected best move from ply " << maxDepth-1 << "\n";

    resetMaxDepth();

    std::cout << "\nMy move is " << encodeSpace(moves[lastIterationFrom].getFrom()) << encodeSpace(moves[lastIterationFrom].getTo()) << " (" << reverseMove(moves[lastIterationFrom]) << ")\n\n";
    board.makeMove(moves[lastIterationFrom]);
    board.drawBoard();
}

// Min, of the minimax algorithm
int Game::min(int depth, int alpha) {
    int minScore = 200000, curScore;

    // Have any kings been taken yet?
    int kingStatus = board.checkBothKings();
    if (kingStatus != 0) return (kingStatus * 1000 * (15 - depth));

    // Are we at max depth? Better turn back then
    if (depth == maxDepth) return evaluate();
    
    // Get all possible moves for the human player
    std::vector<Move> moves = board.getHumanMoves();
    std::sort(moves.begin(), moves.end());

    // If there are no human moves remaining, that's GREAT for the computer player!
    if (moves.size() == 0) return 1000 * (15 - depth);

    // For each move found, make the move, minimax, then undo it
    size_t i;
    for (i = 0; i < moves.size(); i++) {
        board.makeMove(moves[i]);
        curScore = max(depth + 1, minScore);
        if (curScore < minScore) {
            minScore = curScore;
        }
        board.undoMove(moves[i]);
        if (minScore <= alpha) {
            return minScore;
        }
        
        // If it's already been 5 seconds, screw this iteration, it's invalid
        if (endTurnNow()) return 9999;
    }

    // Delete vector
    return minScore;
}

// Max, of the minimax algorithm
int Game::max(int depth, int beta) {
    int maxScore = -200000, curScore;

    // Have any kings been taken yet?
    int kingStatus = board.checkBothKings();
    if (kingStatus != 0) return (kingStatus * 1000 * (15 - depth));

    // Are we at max depth? Better turn back then
    if (depth == maxDepth) return evaluate();

    // Get all possible moves for the computer player
    std::vector<Move> moves = board.getComputerMoves();
    std::sort(moves.begin(), moves.end());

    // If there are no computer moves remaianing, that SUCKS for the computer player!
    if (moves.size() == 0) return -1000 * (15 - depth);

    // For each move found, make the move, minimax, then undo it
    size_t i;
    for (i = 0; i < moves.size(); i++) {
        board.makeMove(moves[i]);
        curScore = min(depth + 1, maxScore);
        if (curScore > maxScore) {
            maxScore = curScore;
        }
        board.undoMove(moves[i]);
        if (maxScore >= beta) {
            return maxScore;
        }
        
        // If it's already been 5 seconds, screw this iteration, it's invalid
        if (endTurnNow()) return -9999;
    }

    // Delete vector
    return maxScore;
}

// Evaluate board state. Could be a lot better.
int Game::evaluate() {
    int pieceCount = 0;
    int pieceBalance = 0;
    for (int i = 0; i < 48; i++) {
        pieceBalance += board.getPieceAt(i) * -1;
        if (board.getPieceAt(i) > 0) {
            pieceCount--;
        } else  if (board.getPieceAt(i) < 0) {
            pieceCount++;
        }
    }
    return (pieceBalance * 0.4 + pieceCount * 0.6) * 10;
    //return pieceBalance;
}

// Check to see if either king has been captured
void Game::checkForGameEnd() {
    int endStatus = board.checkBothKings();
    if (endStatus != 0) {
        gameEnd(endStatus * -1);
    }
}

// If the game has ended, print out result
void Game::gameEnd(int humanWins) {
    if (humanWins > 0) {
        std::cout << "Congratulations, you win!\n";
    } else {
        std::cout << "Sorry, you lose!\n";
    }
    std::string in;
    while(true) {
        std::cin >> in;
    }
}
