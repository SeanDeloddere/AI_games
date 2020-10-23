#include "player.hpp"
#include <cstdlib>
#include <math.h>
#include <limits.h>

namespace TICTACTOE3D
{
int miniMax(const GameState& pState, uint8_t player, int alpha, int beta, int depth);

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    //if there are no next states return the current game state?
    if (lNextStates.size() == 0) return GameState(pState, Move());

    int depth = 0; //change this around
    if (lNextStates.size() < 5) {
        depth = 4;
    }
    else if (lNextStates.size() < 10) {
        depth = 3;
    }
    else if (lNextStates.size() < 25) {
        depth = 2;
    }
    else if (lNextStates.size() < 50) {
        depth = 1;
    }

    int alpha = INT_MIN;
    int beta = INT_MAX;
    int best = INT_MIN;
    int bestIndex;

    for (unsigned int i = 0; i < lNextStates.size(); i++) {
        int cur = 0;
        cur = miniMax(lNextStates[i], pState.getNextPlayer(), alpha, beta, depth);
        if (cur >= best) {
            best = cur;
            bestIndex = i;
        }
    }

    return lNextStates[bestIndex];
}

int heur(const GameState& pState, uint8_t player) {
    int rewards[5][5] = { {0,-10,-100,-1000,-10000}, {10,0,0,0,0}, {100,0,0,0,0}, {1000,0,0,0,0}, {10000,0,0,0,0} };

    int score = 0;
    int x;//amount of X's on same line
    int o;//amount of O's on same line

    
    //==================================== straights ====================================

    //check verticals
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x = 0;
            o = 0;
            for (int n = 0; n < 4; n++) {
                if (pState.at(i, j, n) == player) {
                    x++;
                }
                else if (pState.at(i, j, n) == (player % 2) + 1) {
                    o++;
                }
            }
            score += rewards[x][o];
        }
    }

    //check columns
    for (int i = 0; i < 4; i++) {
        for (int n = 0; n < 4; n++) {
            x = 0;
            o = 0;
            for (int j = 0; j < 4; j++) {
                if (pState.at(i, j, n) == player) {
                    x++;
                }
                else if (pState.at(i, j, n) == (player % 2) + 1) {
                    o++;
                }
            }
            score += rewards[x][o];
        }
    }

    //check rows
    for (int n = 0; n < 4; n++) {
        for (int j = 0; j < 4; j++) {
            x = 0;
            o = 0;
            for (int i = 0; i < 4; i++) {
                if (pState.at(i, j, n) == player) {
                    x++;
                }
                else if (pState.at(i, j, n) == (player % 2) + 1) {
                    o++;
                }
            }
            score += rewards[x][o];
        }
    }

    //==================================== diagonals ====================================

    //for 2nd diagonal
    int x2;//amount of X's on same line
    int o2;//amount of O's on same line

    //check diagonals for each row
    for (int i = 0; i < 4; i++) {
        //1st diagonal
        x = 0;
        o = 0;

        //2nd diagonal
        x2 = 0;
        o2 = 0;

        for (int j = 0; j < 4; j++) {
            if (pState.at(i, j, j) == player) {
                x++;
            }
            else if (pState.at(i, j, j) == (player % 2) + 1) {
                o++;
            }
            if (pState.at(i, 3-j, j) == player) {
                x2++;
            }
            else if (pState.at(i, 3-j, j) == (player % 2) + 1) {
                o2++;
            }
        }
        score += rewards[x][o];
        score += rewards[x2][o2];

    }

    //check diagonals for each column
    for (int i = 0; i < 4; i++) {
        //1st diagonal
        x = 0;
        o = 0;

        //2nd diagonal
        x2 = 0;
        o2 = 0;

        for (int j = 0; j < 4; j++) {
            if (pState.at(j, i, j) == player) {
                x++;
            }
            else if (pState.at(j, i, j) == (player % 2) + 1) {
                o++;
            }
            if (pState.at(3-j, i, j) == player) {
                x2++;
            }
            else if (pState.at(3-j, i, j) == (player % 2) + 1) {
                o2++;
            }
        }
        score += rewards[x][o];
        score += rewards[x2][o2];

    }

    //check diagonals for each vertical
    for (int i = 0; i < 4; i++) {
        //1st diagonal
        x = 0;
        o = 0;

        //2nd diagonal
        x2 = 0;
        o2 = 0;

        for (int j = 0; j < 4; j++) {
            if (pState.at(j, j, i) == player) {
                x++;
            }
            else if (pState.at(j, j, i) == (player % 2) + 1) {
                o++;
            }
            if (pState.at(3 - j, j, i) == player) {
                x2++;
            }
            else if (pState.at(3 - j, j, i) == (player % 2) + 1) {
                o2++;
            }
        }
        score += rewards[x][o];
        score += rewards[x2][o2];

    }


    //==================================== 3d-diagonals ====================================
    
    //1st diagonal
    x = 0;
    o = 0;

    //2nd diagonal
    x2 = 0;
    o2 = 0;

    //3rd diagonal
    int x3 = 0;
    int o3 = 0;

    //4th diagonal
    int x4 = 0;
    int o4 = 0;

    for (int i = 0; i < 4; i++) {
        //1st diagonal
        if (pState.at(i, i, i) == player) {
            x++;
        }
        else if (pState.at(i, i, i) == (player % 2) + 1) {
            o++;
        }
        
        //2nd diagonal
        if (pState.at(3-i, i, i) == player) {
            x2++;
        }
        else if (pState.at(3-i, i, i) == (player % 2) + 1) {
            o2++;
        }

        //3rd diagonal
        if (pState.at(i, 3-i, i) == player) {
            x3++;
        }
        else if (pState.at(i, 3-i, i) == (player % 2) + 1) {
            o3++;
        }

        //4th diagonal
        if (pState.at(i, i, 3-i) == player) {
            x4++;
        }
        else if (pState.at(i, i, 3-i) == (player % 2) + 1) {
            o4++;
        }
    }

    score += rewards[x][o];
    score += rewards[x2][o2];
    score += rewards[x3][o3];
    score += rewards[x4][o4];

    if (player == CELL_O) {
        score = -score;
    }


    return score;
}

int miniMax(const GameState& pState, uint8_t player, int alpha, int beta, int depth) {

    std::vector<GameState> curNextStates;
    pState.findPossibleMoves(curNextStates);

    int score = 0;
    if (depth == 0) {
        score = heur(pState,player);
    }
    else if (pState.isEOG() || curNextStates.size() == 0) {
        if (pState.isXWin()) {
            score = INT_MAX;
        }
        else if (pState.isOWin()) {
            score = INT_MIN;
        }
        else {
            score = 0;
        }
    }
    else if (player == CELL_X) {
        score = INT_MIN;
        for (unsigned int i = 0; i < curNextStates.size(); i++) {
            int next = miniMax(curNextStates[i], CELL_O, alpha, beta, depth - 1);
            if (next > score) {
                score = next;
            }
            if (score > alpha) {
                alpha = score;
            }
            if (beta <= alpha) {
                break;
            }
        }
    }
    else if (player == CELL_O) {
        score = INT_MAX;
        for (unsigned int i = 0; i < curNextStates.size(); i++) {
            int next = miniMax(curNextStates[i], CELL_X, alpha, beta, depth - 1);
            if (next < score) {
                score = next;
            }
            if (score < beta) {
                beta = score;
            }
            if (beta <= alpha) {
                break;
            }
        }
    }
    return score;
}
/*namespace TICTACTOE3D*/ }
