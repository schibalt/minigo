/*
* Board.cpp
*
*  Created on: Nov 18, 2013
*      Author: tiliska
*/

#include "Board.h"
#include "Space.h"
#include <omp.h>

#define DEFAULTDIMENSIONS 19

Board::Board()
{
    initialize (DEFAULTDIMENSIONS);
}

Board::Board (char dimensions)
{
    initialize (dimensions);
}

Board::~Board()
{
    for (char space = 0; space < dimensions; space++)
        delete[] spaces[space];

    delete[] spaces;

    //pieces are already being deleted when space matrix is
    //while (!pieces.empty())
    //    delete pieces.back(),
    //           pieces.pop_back();
    /*for (vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it)
        delete *it;*/
}

Board* Board::clone()
{
    Board* boardClone = new Board (dimensions);

    //#pragma omp parallel for
    for (vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it)
        boardClone->addPiece ( (*it)->clone());

    return boardClone;
}

void Board::initialize (char dimensions)
{
    //pieces = new vector<Piece>();
    this->dimensions = dimensions;
    spaces = new Space*[dimensions];

    for (char space = 0; space < dimensions; space++)
        spaces[space] = new Space[dimensions];
}

char Board::getDimensions()
{
    return dimensions;
}

Space Board::getSpace (char x, char y)
{
    return spaces[x][y];
}

//void Board::addPiece (Piece newPiece)
//{
//    if (getSpace (newPiece.getPoint().x, newPiece.getPoint().y).isEmpty())
//    {
//        pieces.push_back (newPiece);
//    }
//    spaces[newPiece.getPoint().x][newPiece.getPoint().y].assignPiece (newPiece);
//}

void Board::addPiece (Piece* newPiece)
{
    if (getSpace (newPiece->getPoint().x, newPiece->getPoint().y).isEmpty())
    {
        pieces.push_back (newPiece);
    }
    spaces[newPiece->getPoint().x][newPiece->getPoint().y].assignPiece (newPiece);
}

short Board::piecesCount()
{
    return pieces.size();
}

Piece Board::pieceAt (short index)
{
    return *pieces[index];
}