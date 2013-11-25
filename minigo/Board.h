/*
 * Board.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Space.h"
#include "Piece.h"
#include <vector>

using std::vector;

class Board {

public:
	Board();
	Board(int dimensions);
	virtual ~Board();
	Space getSpace(int, int);
	int getDimensions();
	Board* clone();
	void addPiece(Piece);

private:
	Space** spaces;
	void initSpaces();
	int dimensions;
	vector<Piece>* pieces;
};

#endif /* BOARD_H_ */
