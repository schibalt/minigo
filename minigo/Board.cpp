/*
* Board.cpp
*
*  Created on: Nov 18, 2013
*      Author: tiliska
*/

#include "Board.h"
#include "Space.h"
#include <omp.h>

#define DEFAULTDIMENSION 19

Board::Board() {

	this->dimensions = DEFAULTDIMENSION;
	initSpaces();
}

Board::Board(int dimensions) {

	this->dimensions = dimensions;
	initSpaces();
}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

Board Board::clone() {

	Board boardClone;

	//#pragma omp parallel for
	for (vector<Piece>::iterator it = pieces.begin(); it != pieces.end(); ++it)
		boardClone.addPiece((*it).clone());

	return boardClone;
}

void Board::initSpaces() {

	spaces = new Space*[dimensions];

	for (int space = 0; space < dimensions; space++)
		spaces[space] = new Space[dimensions];
}

int Board::getDimensions() {

	return dimensions;
}

Space Board::getSpace(int x, int y) {

	return spaces[x][y];
}

void Board::addPiece(Piece newPiece){

	if(getSpace(newPiece.point.x, newPiece.point.y).isEmpty()){

		pieces.push_back(newPiece);
	}
}
