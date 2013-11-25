/*
 * Space.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Space.h"

#define NOPIECE 10

Space::Space() {

	emptyFlag = true;
	piece = 0;
}

Space::~Space() {
	// TODO Auto-generated destructor stub
}

bool Space::isEmpty() {
	return emptyFlag;
}

Piece Space::getPiece() {

	if (emptyFlag)
		throw NOPIECE;
	else
		return *piece;
}
