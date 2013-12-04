/*
 * Piece.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <QDebug>

class Piece
{
public:

    enum colors
    {
        BLACK = 0,
        WHITE = 1
    };
    Piece (colors color, unsigned char x, unsigned char y);
    Piece (const Piece &obj);
    virtual ~Piece();
    Piece & operator= (const Piece& that);

    colors getColor();
    static const char* getColorName (colors color);
    unsigned char getX(), getY();
    //Piece* clone();

private:
    colors color;
    unsigned char x, y;
};

#endif /* PIECE_H_ */
