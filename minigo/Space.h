/*
 * Space.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Piece.h"

#ifndef SPACE_H_
#define SPACE_H_

class Space{

public:
	Space();
	virtual ~Space();
	bool isEmpty();
	Piece getPiece();
	void assignPiece(Piece* piece);

private:
	bool emptyFlag;
	Piece* piece;
};

#endif /* SPACE_H_ */
