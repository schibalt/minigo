/*
 * State.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef STATE_H_
#define STATE_H_

#include "Board.h"
#include "Player.h"
#include "State.h"
#include "boost/ptr_container/ptr_vector.hpp"

class State {

public:
	State(unsigned char dimensions, bool color, unsigned char plies);
	State(Board* preconstructedBoard, bool color, unsigned char plies);
	virtual ~State();

	short blackPoints, whitePoints;
	State& subStateAt(size_t stateIdx);
 	State* releaseSubStateAt(size_t stateIdx);
	void generateSubsequentStatesAfterMove(unsigned char level);
	short subStatesCount();
	unsigned char getDimensions();
	unsigned short piecesCount();
	Piece pieceAt(unsigned short index);
	bool hasAnySubsequentStates();
	unsigned char x, y;

private:
	Board* board;
	bool color;
	void initialize(Board* board, bool color, unsigned char plies);
	boost::ptr_vector<State> subsequentStates;
	void generateSubsequentStates(bool color, unsigned char level);
};

#endif /* STATE_H_ */
