/*
* Board.cpp
*
*  Created on: Nov 18, 2013
*      Author: tiliska
*/

#include "Board.h"

Board::Board (unsigned char dimensions)
{
    initialize (dimensions);

    for (short space = dimensions * dimensions; space > 0; --space)
        spaces.push_back (new Space());
}

//Board::Board (unsigned char dimensions, boost::ptr_vector<Space> spaces)
//{
//    initialize (dimensions);
//
//    for (boost::ptr_vector<Space>::iterator spiterator = spaces.begin(); spiterator != spaces.end(); ++spiterator)
//        this->spaces.push_back (& (*spiterator));
//}

Board::Board (const Board &that)
{
    dimensions = that.dimensions;
    spaces = that.spaces;
    pieces = that.pieces;
}

Board::~Board()
{
    /* for (unsigned char space = 0; space < dimensions; space++)
         delete[] spaces[space];

     delete[] spaces;*/
}

Board&  Board::operator= (const Board& that)
{
    Board temporary (that);
    return *this;
}

void Board::initialize (unsigned char dimensions)
{
    this->dimensions = dimensions;
    /*spaces = new Space*[this->dimensions];

    for (unsigned char space = 0; space < this->dimensions; space++)
        spaces[space] = new Space[this->dimensions];*/
}

//Board* Board::clone()
//{
//    Board* boardClone = new Board (dimensions);
//
//    for (boost::ptr_vector<Piece>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter)
//        boardClone->addPiece (iter);
//
//    return boardClone;
//}

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
    if (spaceIsEmpty (newPiece->getX(), newPiece->getY()))
    {
        pieces.push_back (newPiece);
    }
    spaces[newPiece->getX() + newPiece->getY() * dimensions].assignPiece (newPiece);
}

unsigned short Board::piecesCount()
{
    return pieces.size();
}

Piece* Board::pieceAt (unsigned short index)
{
    return &pieces.at (index);
    //return (*copiedPieces)[index];
}

bool Board::moveIsLegal (Piece::colors color, unsigned char x, unsigned char y)
{
    return spaceIsEmpty (x, y); // && !chainWillBeCaptured(color, x, y);
}

bool Board::outOfBounds (unsigned char x, unsigned char y)
{
    return x < 0 || x >= dimensions || y < 0 || y >= dimensions;
}

bool Board::spaceIsEmpty (unsigned char x, unsigned char y)
{
    return spaces[x + y * dimensions].isEmpty();
}

bool Board::spaceIsSameColor (Piece::colors color, unsigned char x, unsigned char y)
{
    if (x < 0 || x >= dimensions || y < 0 || y >= dimensions)
        throw;
    if (spaceIsEmpty (x, y))
        throw;

    return spaces[x + y * dimensions].isSameColor ( (Piece::colors) color);
}

bool Board::chainWillBeCaptured (Piece::colors color, unsigned char x, unsigned char y)
{
    bool noRowLiberty = true;
    bool noUpperLiberty = true;
    bool noLowerLiberty = true;

    for (char row = 0; row < 3; ++row)
    {
        switch (row)
        {
        case 0:
            if (spaceIsEmpty (x - 1, y) || spaceIsEmpty (x + 1, y))
                noRowLiberty = false;
            else
                noRowLiberty = chainWillBeCaptured (color, x - 1, y)
                               && chainWillBeCaptured (color, x + 1, y);
            break;
        case 1:
            if (spaceIsEmpty (x, y - 1))
                noUpperLiberty = false;
            else
                noUpperLiberty = chainWillBeCaptured (color, x , y - 1);
            break;
        case 2:
            if (spaceIsEmpty (x, y + 1))
                noLowerLiberty = false;
            else
                noLowerLiberty = chainWillBeCaptured (color, x, y + 1);
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
        if (iter->getColor() == Piece::WHITE)
            whitePieces++;
    return whitePieces;
}

unsigned short Board::getNumBlackPieces()
{
    unsigned short blackPieces = 0;
    for (boost::ptr_vector<Piece>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter)
        if (iter->getColor() == Piece::BLACK)
            blackPieces++;
    return blackPieces;
}

unsigned short Board::computeTerritory (Piece::colors color)
{
    unsigned short territory = 0;
    bool *checkedCoordinates  = new bool[dimensions * dimensions];
    for (unsigned short checkedCoordinate = 0; checkedCoordinate < dimensions * dimensions; ++checkedCoordinate)
    {
        unsigned char row = (checkedCoordinate / dimensions) * dimensions,
			column = checkedCoordinate % dimensions;
        unsigned short index = row + column;
        checkedCoordinates[index] = false;
    }

	//output the pieces for debug
    /*for (boost::ptr_vector<Piece>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter)
        qDebug() << Piece::getColorName (iter->getColor()) << "piece at" << iter->getX() << "," << iter->getY();
    qDebug();*/

    //#pragma omp parallel for schedule(dynamic) reduction(+:territory)
    for (short y = 0; y < dimensions; ++y)
    {
        for (short x = 0; x < dimensions; ++x)
        {
            checkedCoordinates[dimensions * y + x] = true;

            if (spaceIsEmpty (x, y))
            {
                //i don't occupy the space but there are no adjacent enemies
                if (!checkedCoordinates[dimensions * y + x] && spaceIsHeldBy (color, x, y, checkedCoordinates))
                    territory++;
            }
            else if (spaceIsSameColor (color, x, y)) //i occupy the space
                territory++;
        }
    }
    delete [] checkedCoordinates;
    return territory;
}

bool Board::spaceIsHeldBy (Piece::colors color, unsigned char x, unsigned char y, bool* checkedCoordinates)
{
//    FIND-PATH(x, y)
//
//if (x, y outside maze) return false
//if (x, y is goal) return true
//if (x, y not open) return false
//mark x, y as part of solution path
//if (FIND-PATH(North of x, y) == true) return true
//if (FIND-PATH(East of x, y) == true) return true
//if (FIND-PATH(South of x, y) == true) return true
//if (FIND-PATH(West of x, y) == true) return true
//unmark x, y as part of solution path
//return false

    checkedCoordinates[dimensions * y + x] = true;

    enum directions
    {
        EAST = 1,
        SOUTH = 2,
        WEST = 3,
        NORTH = 4
    };
    vector<directions> divections (0);
    divections.push_back (EAST);
    divections.push_back (SOUTH);
    divections.push_back (WEST);
    divections.push_back (NORTH);

	printCheckedSpaces(checkedCoordinates);

    for ( char checkingAdjacent = 1; checkingAdjacent > -1; --checkingAdjacent)
        //for (directions direction = EAST; direction < 5; direction++)
        for (vector<directions>::iterator diterator = divections.begin(); diterator != divections.end(); ++diterator)
        {
			short xoffset = INT_MIN, yoffset = INT_MIN;

            switch (*diterator)
            {
            case 1://east
                xoffset = x + 1, yoffset = y;
                break;
            case 2://south
                xoffset = x, yoffset = y + 1;
                break;
            case 3://west
                xoffset = x - 1, yoffset = y;
                break;
            case 4://north
                xoffset = x, yoffset = y - 1;
                break;
            }

            if (!outOfBounds (xoffset, yoffset))
            {
                switch (checkingAdjacent)
                {
                case 0://traverse
                    if (spaceIsEmpty (xoffset, yoffset) && !checkedCoordinates[dimensions * yoffset + xoffset])
                        return spaceIsHeldBy (color, xoffset, yoffset, checkedCoordinates);
                    break;
                case 1://adjacent
                    if (!spaceIsEmpty (xoffset, yoffset) && !spaceIsSameColor (color, xoffset, yoffset))
                        return false;
                    break;
                }
            }
        }//directions loop
    return true;
}

void Board::printCheckedSpaces (bool* checkedCoordinates)
{

    //print checked flags
    QDebug debug = qDebug();
    for (unsigned short checkedCoordinate = 0; checkedCoordinate < dimensions * dimensions; ++checkedCoordinate)
    {
        char row = (checkedCoordinate / dimensions) * dimensions;
        char column = checkedCoordinate % dimensions;
        unsigned short index = row + column;
        checkedCoordinate % dimensions == 0 ?
        debug << "\n" << checkedCoordinates[index] << " "
              : debug << checkedCoordinates[index] << " ";
    }
    //\print checked flags
}