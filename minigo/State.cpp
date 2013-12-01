/*
* State.cpp
*
*  Created on: Nov 18, 2013
*      Author: tiliska
*/

#include "State.h"
#include "Board.h"
#include "Piece.h"
//#include <iostream>
#include <QDebug>
#include <omp.h>

using std::swap;
using boost::iterator;

State::State (unsigned char dimensions, bool color, unsigned char plies)
{
    Board* board = new Board (dimensions);
    initialize (board, color, plies);
}

State::State (Board* preconstructedBoard, bool color, unsigned char plies)
{
    initialize (preconstructedBoard, color, plies);
}

void State::initialize (Board* board, bool color, unsigned char plies)
{
    this->color = color;
    this->board = board;
    whitePoints = NULL, blackPoints = NULL, x = NULL, y = NULL;
    generateSubsequentStates((color + 1) % 2, plies);
}

State::~State()
{
    //boost::ptr_vector<State>::iterator it;
    //for (it=subsequentStates.begin(); it < subsequentStates.end();/*no iterator increment*/ )
//       it = subsequentStates.erase(it);
    delete board;
}

/*
* for each possible state
* 1. clone current board
* 2. ask board to place piece
*/
void State::generateSubsequentStates (bool color, unsigned char level)
{
    if (level > 0)
    {
        unsigned char dimensions = board->getDimensions();
        short subStatesGenerated = 0;

        #pragma omp parallel for //reduction(+:subStatesGenerated)// default(none)
        for (char y = 0; y < dimensions; y++)
        {
            for (char x = 0; x < dimensions; x++)
            {
                if (board->moveIsLegal (color, x, y))
                {
                    Board* newBoard = board->clone();
                    Piece* newPiece = new Piece (color, x, y);
                    newBoard->addPiece (newPiece);

                    State* subsequentState = new State (newBoard, color, level - 1);
                    subStatesGenerated++;
                    //subStatesGenerated += subsequentState->generateSubsequentStates ( (color + 1) % 2, level - 1) + 1;
                    #pragma omp critical
                    subsequentStates.push_back (subsequentState);
                    //qDebug()  << "generated state" << y * dimensions + x << "at level" << QString::number(level);
                    //qDebug() << "new state generated at row" << QString::number(y) << "col" << QString::number(x);
                }//if
            }//x
        }//y
        qDebug() << subStatesGenerated << "subsequent states generated at level" << level;
    }//if
	else
	{
		//compute player heuristics
	}
}//generateSubsequentStates

State& State::subStateAt (size_t stateIdx)
{
    return subsequentStates[stateIdx];
}

State* State::releaseSubStateAt (size_t stateIdx)
{
    State * chosenState = subsequentStates.release(subsequentStates.begin() + stateIdx).release();
    subsequentStates.release();
    return chosenState;
}

short State::subStatesCount()
{
    return subsequentStates.size();
}

void State::generateSubsequentStatesAfterMove(unsigned char level)
{
    //unsigned short gssamloops = 0;
    if(level > 1)
    {
        for (boost::ptr_vector<State>::iterator iter = subsequentStates.begin(); iter != subsequentStates.end(); ++iter)
        {
            iter->generateSubsequentStatesAfterMove(level - 1);
            //gssamloops++;
        }
    }
    else
    {
        for (boost::ptr_vector<State>::iterator iter = subsequentStates.begin(); iter != subsequentStates.end(); ++iter)
        {
            iter->generateSubsequentStates(color, level);
            //gssamloops++;
        }
    }
    //qDebug() << "gssamloops" << gssamloops;
}

unsigned char State::getDimensions()
{
    return board->getDimensions();
}

unsigned short State::piecesCount()
{
    return board->piecesCount();
}

Piece State::pieceAt (unsigned short index)
{
    return board->pieceAt(index);
}

bool State::hasAnySubsequentStates()
{
    return subsequentStates.size() > 0;
}