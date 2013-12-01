/*
 * Piece.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Piece.h"

Piece::Piece (bool color, unsigned char x, unsigned char y)
{
    this->color = color;
	this->x = x;
	this->y = y;
}

Piece::~Piece()
{
}

bool Piece::getColor()
{
    return color;
}

Piece* Piece::clone()
{
    Piece* clonePiece = new Piece (color, x, y);
    return clonePiece;
}

unsigned char Piece::getX()
{
	return x;
}

unsigned char Piece::getY()
{
	return y;
}
