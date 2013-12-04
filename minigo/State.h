/*
 * State.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef STATE_H_
#define STATE_H_

#include "Board.h"
#include "time.h"

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)
#define ABS(n) (-n)

class State
{
public:
    State (unsigned char dimensions, bool color, unsigned char plies);
    State (Board* preconstructedBoard, bool color, unsigned char plies);
    virtual ~State();

    State& subStateAt (size_t stateIdx);
    State* releaseSubStateAt (size_t stateIdx);
    Piece* pieceAt (unsigned short index);

    void generateSubsequentStatesAfterMove (unsigned char level);
    void changeColor();
    void makeMove (unsigned char x, unsigned char y);

    short subStatesCount();
    unsigned char getDimensions();
    unsigned short piecesCount();
    bool hasAnySubsequentStates();

    short blackPoints, whitePoints;
    unsigned char x, y;

private:
    Board* board;
    bool color;
    boost::ptr_vector<State> subsequentStates;

    void initialize (Board* board, bool color, unsigned char plies);
    void generateSubsequentStates (Piece::colors color, unsigned char level);
};

#endif /* STATE_H_ */
