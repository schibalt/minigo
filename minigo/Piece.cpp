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
	/*this->x = new char[1];
	this->y = new char[1];
	this->x[0] = x;
	this->y[0] = y;*/
    //this->point = Point (i, j);
}

Piece::~Piece()
{
	//delete point;
	//delete x, delete y;
}

bool Piece::getColor()
{
    return color;
}

Piece* Piece::clone()
{
    Piece* clonePiece = new Piece (color, x, y);
    //Piece* clonePiece = new Piece (color, x[0], y[0]);
    //Piece* clonePiece = new Piece (color, point.x, point.y);
    //Piece* clonePiece = new Piece (color, point->x, point->y);
    return clonePiece;
}

//Piece::Point Piece::getPoint()
//{
//	return point;
//}

unsigned char Piece::getX()
{
	return x;
}

unsigned char Piece::getY()
{
	return y;
}
