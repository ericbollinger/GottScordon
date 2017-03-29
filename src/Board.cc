#include "Board.h"

Board::Board() {
    for (int i = 0; i < 48; i++) {
        board.push_back(0);
    }

    board[4] = 5;
    board[6] = 2;
    board[7] = 3;
    board[8] = 4;
    board[9] = 4;
    board[10] = 3;
    board[11] = 2;
    board[14] = 1;
    board[15] = 1;
    board[32] = -1;
    board[33] = -1;
    board[36] = -2;
    board[37] = -3;
    board[38] = -4;
    board[39] = -4;
    board[40] = -3;
    board[41] = -2;
    board[43] = -5; 
}

char Board::drawPiece(int p) {
    return "KRBNP pnbrk"[p+5];
}

void Board::drawBoard() {
    for (int i = 7; i >= 0; i--) {
        std::cout << i+1 << " ";
        for (int j = 0; j < 6; j++) {
            int piece = i*6+j;
            if ((i+j)%2 == 0) {
                std::cout << "\033[1;47;30m " << drawPiece(board[piece]) << " \033[0m";
            } else {
                std::cout << "\033[1;46;37m " << drawPiece(board[piece]) << " \033[0m";
            }
        }
        std::cout << "\n";
    }

    std::cout << "   ";
    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0: std::cout << 'A';
                    break;
            case 1: std::cout << 'B';
                    break;
            case 2: std::cout << 'C';
                    break;
            case 3: std::cout << 'D';
                    break;
            case 4: std::cout << 'E';
                   break;  
            case 5: std::cout << 'F';
                   break;
            default: std::cout << 'Z';
        }
        std::cout << "  ";
    }
    std::cout << "\n\n";
}

int Board::getPieceAt(int n) {
    return board[n];
}

void Board::makeMove(Move move) {
    switch (move.getPieceFrom()) {
        case 2: board[move.getTo()] = 4;
                break;
        case 3: board[move.getTo()] = 2;
                break;
        case 4: board[move.getTo()] = 3;
                break;
        case -2: board[move.getTo()] = -4;
                 break;
        case -3: board[move.getTo()] = -2;
                 break;
        case -4: board[move.getTo()] = -3;
                 break;
        default: board[move.getTo()] = board[move.getFrom()];
    }
    board[move.getFrom()] = 0;
}

void Board::undoMove(Move move) {
    board[move.getFrom()] = move.getPieceFrom();
    board[move.getTo()] = move.getPieceTo();
}

int  Board::checkBothKings() {
    int playerKing = 0;
    int cpuKing = 0;
    for (int i = 0; i < 6; i++) {
        if (board[i] == 5) {
            playerKing = -1;
            i = 6;
        }
    }
    for (int i = 42; i < 48; i++) {
        if (board[i] == -5) {
            cpuKing = 1;
            i = 48;
        }
    }
    return playerKing + cpuKing;
}

std::vector<Move> Board::getHumanMoves() {
    std::vector<Move> result;
    int n;
    for (int i = 0; i < 48; i++) {
        switch (board[i]) {
            // king
            case 5:
                // move left
                if (i == 0 || board[i-1] > 0) break;
                result.push_back(Move(i,board[i],i-1,board[i-1],(board[i-1]<0)));

                // move right, if capturing
                if (board[i+1] < 0) {
                    result.push_back(Move(i,board[i],i+1,board[i+1],true));
                }
                break;

            // rook
            case 4:
                // move up
                n = 1;
                while (i+n*6 < 48) {
                    if (board[i+n*6] > 0) break;
                    result.push_back(Move(i,board[i],i+n*6,board[i+n*6],(board[i+n*6]<0)));
                    if (board[i+n*6] < 0) break;
                    n++;
                }
                // move left
                n = 1;
                while ((i-n)%6 != 5 && i-n >= 0) {
                    if (board[i-n] > 0) break;
                    result.push_back(Move(i,board[i],i-n,board[i-n],(board[i-n]<0)));
                    if (board[i-n] < 0) break;
                    n++;
                }
                // move right
                n = 1;
                while ((i+n)%6 != 0 && i+n < 48) {
                    if (board[i+n] > 0) break;
                    result.push_back(Move(i,board[i],i+n,board[i+n],(board[i+n]<0)));
                    if (board[i+n] < 0) break;
                    n++;
                }
                // move down, if capturing
                n = 1;
                while (i-n*6 >= 0) {
                    if (board[i-n*6] > 0) break;
                    if (board[i-n*6] < 0) {
                        result.push_back(Move(i,board[i],i-n*6,board[i-n*6],true));
                        break;
                    }
                    n++;
                }
                break;

            // bishop
            case 3:
                // move up-left 
                n = 1;
                while ((i-n)%6 != 5 && i+n*5<48) {
                    if (board[i+n*5] > 0) break;
                    result.push_back(Move(i,board[i],i+n*5,board[i+n*5],(board[i+n*5]<0)));
                    if (board[i+n*5] < 0) break;
                    n++;
                }
                // move up-right
                n = 1;
                while ((i+n)%6 != 0 && i+n*7<48) {
                    if (board[i+n*7] > 0) break;
                    result.push_back(Move(i,board[i],i+n*7,board[i+n*7],(board[i+n*7]<0)));
                    if (board[i+n*7] < 0) break;
                    n++;
                }
                // move down-left, if capturing
                n = 1;
                while ((i-n)%6 != 5 && i-n*7>=0) {
                    if (board[i-n*7] > 0) break;
                    if (board[i-n*7] < 0) {
                        result.push_back(Move(i,board[i],i-n*7,board[i-n*7],true));
                        break;
                    }
                    n++;
                }
                // move down-right, if capturing
                n = 1;
                while ((i+n)%6 != 0 && i-n*5>=0) {
                    if (board[i-n*5] > 0) break;
                    if (board[i-n*5] < 0) {
                        result.push_back(Move(i,board[i],i-n*5,board[i-n*5],true));
                        break;
                    }
                    n++;
                }
                break;

            // knight
            case 2:
                // move up two, left one 
                if (i <= 35 && i%6 != 0 && board[i+11] <= 0) {
                    result.push_back(Move(i,board[i],i+11,board[i+11],(board[i+11]<0)));
                }
                // move up two, right one
                if (i <= 34 && i%6 != 5 && board[i+13] <= 0) {
                    result.push_back(Move(i,board[i],i+13,board[i+13],(board[i+13]<0)));
                }
                // move up one, left two
                if (i <= 41 && i%6 != 1 && i%6 != 0 && board[i+4] <= 0) {
                    result.push_back(Move(i,board[i],i+4,board[i+4],(board[i+4]<0)));
                }
                // move up one, right two
                if (i <= 39 && i%6 != 5 && i%6 != 4 && board[i+8] <= 0) {
                    result.push_back(Move(i,board[i],i+8,board[i+8],(board[i+8]<0)));
                }
                // move down two, left one if capturing
                if (i >= 13 && i%6 != 0 && board[i-13] < 0) {
                    result.push_back(Move(i,board[i],i-13,board[i-13],true));
                }
                // move down two, right one if capturing
                if (i >= 12 && i%6 != 5 && board[i-11] < 0) {
                    result.push_back(Move(i,board[i],i-11,board[i-11],true));
                }
                // move down one, left two if capturing
                if (i >= 8 && i%6 != 1 && i%6 != 0 && board[i-8] < 0) {
                    result.push_back(Move(i,board[i],i-8,board[i-8],true));
                }
                // move down one, right two if capturing
                if (i >= 6 && i%6 != 5 && i%6 != 4 && board[i-4] < 0) {
                    result.push_back(Move(i,board[i],i-4,board[i-4],true));
                }
                break;

            // pawn
            case 1:
                if (i <= 41) {
                    // move forward
                    if (board[i+6] == 0) {
                        result.push_back(Move(i,board[i],i+6,board[i+6],false));
                    }
                    // attack up-left
                    if (i%6 != 0 && board[i+5] < 0) {
                        result.push_back(Move(i,board[i],i+5,board[i+5],true));
                    }
                    // attack up-right
                    if (i%6 != 5 && board[i+7] < 0) {
                        result.push_back(Move(i,board[i],i+7,board[i+7],true));
                    }
                }
                break;

            default: break;
        }
    }

    return result;
}

std::vector<Move> Board::getComputerMoves() {
    std::vector<Move> result;
    int n;
    for (int i = 47; i >= 0; i--) {
        switch(board[i]) {
            //king
            case -5:
                // move right
                if (i == 47 || board[i+1] < 0) break;
                result.push_back(Move(i,board[i],i+1,board[i+1],(board[i+1]>0)));

                // move left, if capturing
                if (board[i-1] > 0 && i > 42) {
                    result.push_back(Move(i,board[i],i-1,board[i-1],true));
                }
                break;

            // rook
            case -4:
                // move down
                n = 1;
                while (i-n*6 >= 0) {
                    if (board[i-n*6] < 0) break;
                    result.push_back(Move(i,board[i],i-n*6,board[i-n*6],(board[i-n*6]>0)));
                    if (board[i-n*6] > 0) break;
                    n++;
                }
                // move left
                n = 1;
                while ((i-n)%6 != 5 && i-n >= 0) {
                    if (board[i-n] < 0) break;
                    result.push_back(Move(i,board[i],i-n,board[i-n],(board[i-n]>0)));
                    if (board[i-n] > 0) break;
                    n++;
                }
                // move right
                n = 1;
                while ((i+n)%6 != 0 && i+n < 48) {
                    if (board[i+n] < 0) break;
                    result.push_back(Move(i,board[i],i+n,board[i+n],(board[i+n]>0)));
                    if (board[i+n] > 0) break;
                    n++;
                }
                // move up
                n = 1;
                while (i+n*6 < 48) {
                    if (board[i+n*6] < 0) break;
                    if (board[i+n*6] > 0) {
                        result.push_back(Move(i,board[i],i+n*6,board[i+n*6],true));
                    }
                    n++;
                }
                break;

            // bishop
            case -3:
                //move down-left
                n = 1;
                while ((i-n)%6 != 5 && i-n*7 >= 0) {
                    if (board[i-n*7] < 0) break;
                    result.push_back(Move(i,board[i],i-n*7,board[i-n*7],(board[i-n*7]>0)));
                    if (board[i-n*7] > 0) break;
                    n++;
                }
                // move down-right
                n = 1;
                while ((i+n)%6 != 0 && i-n*5 >= 0) {
                    if (board[i-n*5] < 0) break;
                    result.push_back(Move(i,board[i],i-n*5,board[i-n*5],(board[i-n*5]>0)));
                    if (board[i-n*5] > 0) break;
                    n++;
                }
                // move up-left, if capturing
                n = 1;
                while ((i-n)%6 != 5 && i+n*5 < 48) {
                    if (board[i+n*5] < 0) break;
                    if (board[i+n*5] > 0) {
                        result.push_back(Move(i,board[i],i+n*5,board[i+n*5],true));
                        break;
                    }
                    n++;
                }
                // move up-right, if capturing
                n = 1;
                while ((i+n)%6 != 0 && i+n*7 < 48) {
                    if (board[i+n*7] < 0) break;
                    if (board[i+n*7] > 0) {
                        result.push_back(Move(i,board[i],i+n*7,board[i+n*7],true));
                        break;
                    }
                    n++;
                }
                break;

            // knight
            case -2:
                // move down two, left one
                if (i >= 13 && i%6 != 0 && board[i-13] >= 0) {
                    result.push_back(Move(i,board[i],i-13,board[i-13],(board[i-13]>0)));
                }
                // move down two, right one
                if (i >= 12 && i%6 != 5 && board[i-11] >= 0) {
                    result.push_back(Move(i,board[i],i-11,board[i-11],(board[i-11]>0)));
                }
                // move down one, left two
                if (i >= 8 && i%6 != 1 && i%6 != 0 && board[i-8] >= 0) {
                    result.push_back(Move(i,board[i],i-8,board[i-8],(board[i-8]>0)));
                }
                // move down one, right two
                if (i >= 6 && i%6 != 5 && i%6 != 4 && board[i-4] >= 0) {
                    result.push_back(Move(i,board[i],i-4,board[i-4],(board[i-4]>0)));
                }
                // move up two, left one, if capturing
                if (i <= 35 && i%6 != 0 && board[i+11] > 0) {
                    result.push_back(Move(i,board[i],i+11,board[i+11],true));
                }
                // move up two, right one, if capturing
                if (i <= 34 && i%6 != 5 && board[i+13] > 0) {
                    result.push_back(Move(i,board[i],i+13,board[i+13],true));
                }
                // move up one, left two, if capturing
                if (i <= 41 && i%6 != 1 && i%6 != 0 && board[i+4] > 0) {
                    result.push_back(Move(i,board[i],i+4,board[i+4],true));
                }
                // move up one, right two, if capturing
                if (i <= 39 && i%6 != 5 && i%6 != 4 && board[i+8] > 0) {
                    result.push_back(Move(i,board[i],i+8,board[i+8],true));
                }
                break;

            // pawn
            case -1:
                if (i >= 6) {
                    // move down
                    if (board[i-6] == 0) {
                        result.push_back(Move(i,board[i],i-6,board[i-6],false));
                    }
                    // attack down-left
                    if (i%6 != 0 && board[i-7] > 0) {
                        result.push_back(Move(i,board[i],i-7,board[i-7],true));
                    }
                    // attack down-right
                    if (i%6 != 5 && board[i-5] > 0) {
                        result.push_back(Move(i,board[i],i-5,board[i-5],true));
                    }
                }
                break;

            default: break;
        }
    }

    return result;
}

int Board::getPieceBalance() {
    int sum = 0;
    for (size_t i = 0; i < 47; i++) {
        if (board[i] > 0) sum--;
        if (board[i] < 0) sum++;
    }
    return sum;
}
