/*
 * Space.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Space.h"

#define NOPIECE 10
#define NULL 0

Space::Space()
{
    emptyFlag = true;
}

Space::~Space()
{
}

bool Space::isSameColor(bool color)
{
	return color == piece->getColor();
}

bool Space::isEmpty()
{
    return emptyFlag;
}

void Space::assignPiece (Piece* piece)
{
    this->piece = piece;
    emptyFlag = false;
}