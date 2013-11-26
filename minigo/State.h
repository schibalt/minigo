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

class State {

public:
	State(int dimensions);
	State(Board* preconstructedBoard);
	virtual ~State();
	void printState();
	Board* board;
	int heuristic;
	int generateSubsequentStates(int color, int level);
	State* stateAt(int stateIdx);

private:
	void initialize(Board* board);
	vector<State*> subsequentStates;
	Player min;
	Player max;
};

#endif /* STATE_H_ */
