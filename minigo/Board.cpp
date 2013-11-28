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

Board::Board (int dimensions)
{
    initialize (dimensions);
}

Board::~Board()
{
    for (int space = 0; space < dimensions; space++)
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

void Board::initialize (int dimensions)
{
    //pieces = new vector<Piece>();
    this->dimensions = dimensions;
    spaces = new Space*[dimensions];

    for (int space = 0; space < dimensions; space++) spaces[space] = new Space[dimensions];
}

int Board::getDimensions()
{
    return dimensions;
}

Space Board::getSpace (int x, int y)
{
    return spaces[x][y];
}

void Board::addPiece (Piece* newPiece)
{
    if (getSpace (newPiece->point.x, newPiece->point.y).isEmpty())
    {
        pieces.push_back (newPiece);
    }
    spaces[newPiece->point.x][newPiece->point.y].assignPiece (newPiece);
}

int Board::piecesCount()
{
    return pieces.size();
}

Piece Board::pieceAt (int index)
{
    return *pieces[index];
}