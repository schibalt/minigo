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
    piece = NULL;
}

Space::~Space()
{
    delete piece;
}

bool Space::isEmpty()
{
    return emptyFlag;
}

Piece Space::getPiece()
{
    if (emptyFlag)
        throw NOPIECE;
    else
        return *piece;
}

void Space::assignPiece (Piece* piece)
{
    this->piece = piece;
}