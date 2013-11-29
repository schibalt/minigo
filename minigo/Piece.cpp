/*
 * Piece.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Piece.h"

Piece::Piece (bool color, char i, char j)
{
    this->color = color;
    this->point = Point (i, j);
}

Piece::~Piece()
{
	//delete point;
}

bool Piece::getColor()
{
    return color;
}

Piece* Piece::clone()
{
    Piece* clonePiece = new Piece (color, point.x, point.y);
    //Piece* clonePiece = new Piece (color, point->x, point->y);
    return clonePiece;
}

Piece::Point Piece::getPoint()
{
	return point;
}
