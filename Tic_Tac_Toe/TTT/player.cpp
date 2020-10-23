#include "player.hpp"
#include <cstdlib>
#include <math.h>
#include <limits.h>


namespace TICTACTOE
{
int miniMax(const GameState& pState, uint8_t player, int alpha, int beta, int depth);

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    //if there are no next states return the current game state?
    if (lNextStates.size() == 0) return GameState(pState, Move());

    int depth = 2; //change this value

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

int heur(const GameState& pState) {//doesnt check if opponent can win atm, might need to improve
    int score = 0;
    int x;//amount of X's on same line (without an O)


    //check rows
    for (int i = 0; i < 4; i++) {
        x = 0;
        for (int j = 0; j < 4; j++) {
            if (pState.at(i, j) == CELL_X) {
                x++;
            }
            else if (pState.at(i, j) == CELL_O) {
                x = 0;
                break;
            }

        }
        if (!(x == 0)) {
            score += pow(2, x);
        }
    }

    //check columns
    for (int j = 0; j < 4; j++) {
        x = 0;
        for (int i = 0; i < 4; i++) {
            if (pState.at(i, j) == CELL_X) {
                x++;
            }
            else if (pState.at(i, j) == CELL_O) {
                x = 0;
                break;
            }

        }
        if (!(x == 0)) {
            score += pow(2, x);
        }
    }

    //check 1st diagonal
    x = 0;
    for (int i = 0; i < 4; i++) {
        if (pState.at(i, i) == CELL_X) {
            x++;
        }
        else if (pState.at(i, i) == CELL_O) {
            x = 0;
            break;
        }
    }
    if (!(x == 0)) {
        score += pow(2, x);
    }

    //check 2nd diagonal
    x = 0;
    for (int i = 0; i < 4; i++) {
        if (pState.at(i, 3 - i) == CELL_X) {
            x++;
        }
        else if (pState.at(i, 3 - i) == CELL_O) {
            x = 0;
            break;
        }
    }
    if (!(x == 0)) {
        score += pow(2, x);
    }

    return score;
}

int miniMax(const GameState& pState, uint8_t player, int alpha, int beta, int depth) {

    std::vector<GameState> curNextStates;
    pState.findPossibleMoves(curNextStates);

    int score = 0;
    if (curNextStates.size() == 0 || depth == 0) {
        score = heur(pState);
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
    else if (player == CELL_O){
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

/*namespace TICTACTOE*/ }
