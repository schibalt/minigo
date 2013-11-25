/*
 * Piece.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Piece.h"

Piece::Piece(int color, int i, int j) {

	this->color = color;
	this->point = Point(i, j);
}

Piece::~Piece() {
	// TODO Auto-generated destructor stub
}

int Piece::getColor() {
	return color;
}

Piece Piece::clone() {

	Piece clonePiece(color, point.x, point.y);
	return clonePiece;
}

//int Piece::Point::getI() {
//	return point.getI();
//}
//
//int Piece::Point::getJ() {
//	return point.getJ();
//}
