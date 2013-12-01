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
	Board(unsigned char dimensions);
	virtual ~Board();

	//Space getSpace(unsigned char x, unsigned char y);
	bool moveIsLegal(bool color, unsigned char x, unsigned char y);
	unsigned char getDimensions();
	Board* clone();
	void addPiece(Piece* piece);
	unsigned short piecesCount();
	Piece pieceAt(unsigned short index);
	bool spaceIsEmpty(unsigned char x, unsigned char y);
	bool spaceIsSameColor(bool color, unsigned char x, unsigned char y); 
	unsigned short getNumWhitePieces();
	unsigned short getNumBlackPieces();

private:
	Space** spaces;
	void initialize(unsigned char dimensions);
	unsigned char dimensions;
	boost::ptr_vector<Piece> pieces;
	bool chainWillBeCaptured(bool color, unsigned char x, unsigned char y);
};

#endif /* BOARD_H_ */
