/*
 * Piece.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef PIECE_H_
#define PIECE_H_

class Piece
{
public:
    Piece (bool color, unsigned char x, unsigned char y);
    virtual ~Piece();
    bool getColor();
    static const bool BLACK = 0;
    static const bool WHITE = 1;
    Piece* clone();
    unsigned char getX(), getY();

private:
    bool color;
    unsigned char x, y;
};

#endif /* PIECE_H_ */
