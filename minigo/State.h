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
	State(char dimensions);
	State(Board* preconstructedBoard);
	virtual ~State();
	void printState();
	Board* board;
	short heuristic;
	short generateSubsequentStates(bool color, char level);
	State* subStateAt(short stateIdx);
	State* subStateAtDeleteOthers(short stateIdx);
	short subStatesCount();
	//State subStateAt(short subStateIdx);
	void clearSubStates();

private:
	void initialize(Board* board);
	vector<State*> subsequentStates;
	/*Player min;
	Player max;*/
};

#endif /* STATE_H_ */
