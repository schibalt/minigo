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
	Board(char dimensions);
	virtual ~Board();
	Space getSpace(char x, char y);
	char getDimensions();
	Board* clone();
	void addPiece(Piece* piece);
	short piecesCount();
	Piece pieceAt(short index);

private:
	Space** spaces;
	void initialize(char dimensions);
	char dimensions;
	vector<Piece*> pieces;
};

#endif /* BOARD_H_ */
