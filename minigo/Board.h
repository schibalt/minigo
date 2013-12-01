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

class Board
{
public:
    Board(unsigned char dimensions);
    virtual ~Board();

    bool moveIsLegal(bool color, unsigned char x, unsigned char y);
    bool spaceIsEmpty(unsigned char x, unsigned char y);
    bool spaceIsSameColor(bool color, unsigned char x, unsigned char y);

    unsigned short piecesCount();
    unsigned short getNumWhitePieces();
    unsigned short getNumBlackPieces();
    unsigned short computeBlackTerritory();
    unsigned short computeWhiteTerritory();

    unsigned char getDimensions();
    Board* clone();
    void addPiece(Piece* piece);
    Piece pieceAt(unsigned short index);

private:
    Space** spaces;
    void initialize(unsigned char dimensions);
    unsigned char dimensions;
    boost::ptr_vector<Piece> pieces;
    bool chainWillBeCaptured(bool color, unsigned char x, unsigned char y);
	bool isHeldBy(bool color, unsigned char x, unsigned char y);
    bool outOfBounds(unsigned char x, unsigned char y);
};

#endif /* BOARD_H_ */
