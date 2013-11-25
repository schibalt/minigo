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
	State(int);
	State(Board);
	virtual ~State();
	void printState();
	Board board;
private:
	vector<State> subsequentStates;
	int generateSubsequentStates(int, int);
	Player min;
	Player max;
};

#endif /* STATE_H_ */
