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
	State(unsigned char dimensions, bool color);
	State(Board* preconstructedBoard, bool color);
	virtual ~State();

	Board* board;
	short heuristic;
	
	short generateSubsequentStates(bool color, unsigned char level);
	State* subStateAt(unsigned short stateIdx);
	State* subStateAtDeleteOthers(unsigned short stateIdx);
	void generateSubsequentStatesAfterMove(unsigned char level);
	short subStatesCount();

private:
	bool color;
	void initialize(Board* board, bool color);
	vector<State*> subsequentStates;
};

#endif /* STATE_H_ */
