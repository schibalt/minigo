/*
* Board.cpp
*
*  Created on: Nov 18, 2013
*      Author: tiliska
*/

#include "Board.h"
#include "Space.h"
#include <omp.h>

Board::Board (unsigned char dimensions)
{
    initialize (dimensions);
}

void Board::initialize (unsigned char dimensions)
{
    this->dimensions = dimensions;
    spaces = new Space*[this->dimensions];

    for (unsigned char space = 0; space < this->dimensions; space++)
        spaces[space] = new Space[this->dimensions];
}

Board::~Board()
{
    for (unsigned char space = 0; space < dimensions; space++)
        delete[] spaces[space];

    delete[] spaces;
}

Board* Board::clone()
{
    Board* boardClone = new Board (dimensions);

    //#pragma omp parallel for
    for (boost::ptr_vector<Piece>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter)
        boardClone->addPiece ( iter->clone());

    return boardClone;
}

unsigned char Board::getDimensions()
{
    return dimensions;
}

//Space Board::getSpace (unsigned char x, unsigned char y)
//{
//    return spaces[x][y];
//}

void Board::addPiece (Piece* newPiece)
{
    //if (getSpace (newPiece->getX(), newPiece->getY()).isEmpty())
    if (spaceIsEmpty(newPiece->getX(), newPiece->getY()))
    {
        pieces.push_back (newPiece);
    }
    spaces[newPiece->getX()][newPiece->getY()].assignPiece (newPiece);
}

unsigned short Board::piecesCount()
{
    return pieces.size();
}

Piece Board::pieceAt (unsigned short index)
{
    return pieces[index];
}

bool Board::moveIsLegal(bool color, unsigned char x, unsigned char y)
{
    return spaceIsEmpty(x, y);// && !chainWillBeCaptured(color, x, y);
}

bool Board::outOfBounds(unsigned char x, unsigned char y)
{
    return x < 0 || x >= dimensions || y < 0 || y >= dimensions;
}

bool Board::spaceIsEmpty(unsigned char x, unsigned char y)
{
    return spaces[x][y].isEmpty();
}

bool Board::spaceIsSameColor(bool color, unsigned char x, unsigned char y)
{
    if(x < 0 || x >= dimensions || y < 0 || y >= dimensions)
        throw;
    if(spaceIsEmpty(x, y))
        throw;

    return spaces[x][y].isSameColor(color);
}

bool Board::chainWillBeCaptured(bool color, unsigned char x, unsigned char y)
{
    bool noRowLiberty = true;
    bool noUpperLiberty = true;
    bool noLowerLiberty = true;

    for(char row = 0; row < 3; ++row)
    {
        switch(row)
        {
        case 0:
            if(spaceIsEmpty(x - 1, y) || spaceIsEmpty(x + 1, y))
                noRowLiberty = false;
            else
                noRowLiberty = chainWillBeCaptured(color, x - 1, y)
                               && chainWillBeCaptured(color, x + 1, y);
            break;
        case 1:
            if(spaceIsEmpty(x, y - 1))
                noUpperLiberty = false;
            else
                noUpperLiberty = chainWillBeCaptured(color, x , y - 1);
            break;
        case 2:
            if(spaceIsEmpty(x, y + 1))
                noLowerLiberty = false;
            else
                noLowerLiberty = chainWillBeCaptured(color, x, y + 1);
            break;
        }
    }
    return noRowLiberty && noUpperLiberty && noLowerLiberty;
    //if(x < 0 || x == dimensions || y < 0 || y == dimensions)
    //    return false;
    //else
    //    for(char row = 0; row < 3; ++row)
    //    {
    //        switch(row)
    //        {
    //        case 0:
    //            return chainWillBeCaptured(color, x - 1, y)
    //                   || chainWillBeCaptured(color, x + 1, y);
    //            break;
    //        case 1:
    //            return chainWillBeCaptured(color, x, y - 1);
    //            break;
    //        case 2:
    //            return chainWillBeCaptured(color, x, y + 1);
    //            break;
    //        }
    //    }
}

unsigned short Board::getNumWhitePieces()
{
    unsigned short whitePieces = 0;
    for (boost::ptr_vector<Piece>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter)
        if(iter->getColor() == Piece::WHITE)
            whitePieces++;
    return whitePieces;
}

unsigned short Board::getNumBlackPieces()
{
    unsigned short blackPieces = 0;
    for (boost::ptr_vector<Piece>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter)
        if(iter->getColor() == Piece::BLACK)
            blackPieces++;
    return blackPieces;
}

unsigned short Board::computeBlackTerritory()
{
    unsigned short territory = 0;

    #pragma omp parallel for schedule(dynamic) reduction(+:territory)
    for(  short y = 0; y < dimensions; ++y)
    {
        for( short x = 0; x < dimensions; ++x)
        {
            if(isHeldBy(Piece::BLACK, x, y))
                territory++;
        }
    }
}

bool Board::isHeldBy(bool color, unsigned char x, unsigned char y)
{
    if(outOfBounds(x, y))
        return false;

    if(!spaceIsEmpty(x, y))
        if(spaceIsSameColor(color, x, y))
            return true;
        else
            return false;

    bool whiteFoundLeft = false,
         whiteFoundRight = false,
         whiteFoundUp = false,
         whiteFoundDown = false;

    for(char row = 0; row < 3; ++row)
    {
        switch(row)
        {
        case 0:
            if(isHeldBy((color + 1) % 2, x - 1, y))
                return false;
            if(isHeldBy((color + 1) % 2, x + 1, y))
                return false;
            break;
        case 1:
            if(isHeldBy((color + 1) % 2, x, y - 1))
                return false;
            break;
        case 2:
            if(isHeldBy((color + 1) % 2, x, y + 1))
                return false;
            break;
        }
    }
}

unsigned short Board::computeWhiteTerritory()
{
    #pragma omp parallel for schedule(dynamic)
    for( short y = 0; y < dimensions; ++y)
    {
        for( short x = 0; x < dimensions; ++x)
        {

        }
    }
}