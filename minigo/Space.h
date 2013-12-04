/*
 * Space.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#include "Piece.h"

#ifndef SPACE_H_
#define SPACE_H_

class Space
{
public:
    Space();
    Space (const Space &obj);
    virtual ~Space();
    Space & operator= (const Space& that);

    bool isEmpty();
    bool isSameColor (Piece::colors color);
    void assignPiece (Piece* piece);

private:
    bool emptyFlag;
    Piece* piece;
};

#endif /* SPACE_H_ */
