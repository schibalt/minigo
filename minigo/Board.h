/*
 * Board.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Space.h"
#include "Piece.h"
#include <vector>
#include "boost/ptr_container/serialize_ptr_vector.hpp"

using std::vector;

class Board {

public:
	Board();
	Board(unsigned char dimensions);
	virtual ~Board();

	Space getSpace(unsigned char x, unsigned char y);
	unsigned char getDimensions();
	Board* clone();
	void addPiece(Piece* piece);
	unsigned short piecesCount();
	Piece pieceAt(unsigned short index);

private:
	Space** spaces;
	void initialize(unsigned char dimensions);
	unsigned char dimensions;
	//vector<Piece*> pieces;
	boost::ptr_vector<Piece> pieces;
};

#endif /* BOARD_H_ */
