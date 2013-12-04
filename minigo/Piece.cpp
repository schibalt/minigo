/*
 * Piece.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Piece.h"

Piece::Piece (colors color, unsigned char x, unsigned char y)
{
    this->color = color;
    this->x = x;
    this->y = y;
}

Piece::Piece (const Piece &obj)
{
    color = obj.color;
    x = obj.x;
    y = obj.y;
}

Piece::~Piece()
{
}

Piece & Piece::operator=(const Piece& that)
{
	Piece temporary(that);
	return *this;
}

Piece::colors Piece::getColor()
{
    return color;
}

//Piece* Piece::clone()
//{
//    Piece* clonePiece = new Piece (color, x, y);
//    return clonePiece;
//}

unsigned char Piece::getX()
{
    return x;
}

unsigned char Piece::getY()
{
    return y;
}

const char* Piece::getColorName (Piece::colors color)
{
    switch (color)
    {
    case Piece::WHITE:
        return "white";
        break;
    case Piece::BLACK:
        return "black";
        break;
    default:
        return "NOT_A_COLOR";
        break;
    }
}