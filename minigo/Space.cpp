/*
 * Space.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Space.h"

//#define NOPIECE 10
//#define NULL 0

Space::Space()
{
    emptyFlag = true;
}

Space::Space(const Space &obj)
{
	emptyFlag = obj.emptyFlag;
	piece = obj.piece;
}

Space::~Space()
{
}

Space & Space::operator=(const Space& that)
{
        Space temporary (that);
        return *this;
}

bool Space::isSameColor(Piece::colors color)
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

//Space* Space::clone()
//{
//	Space* cloneSpace = new Space();
//}