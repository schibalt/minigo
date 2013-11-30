/*
* State.cpp
*
*  Created on: Nov 18, 2013
*      Author: tiliska
*/

#include "State.h"
#include "Board.h"
#include "Piece.h"
#include <cstdio>
#include <iostream>
#include <QDebug>
#include <omp.h>

using std::swap;
using std::cout;
using std::endl;

State::State (unsigned char dimensions, bool color)
{
    Board* board = new Board (dimensions);
    initialize (board, color);
}

State::State (Board* preconstructedBoard, bool color)
{
    initialize (preconstructedBoard, color);
}

void State::initialize (Board* board, bool color)
{
    this->color = color;
    this->board = board;
    heuristic = NULL;
}

State::~State()
{
    delete board;

    while(!subsequentStates.empty())
        delete subsequentStates.back(),
               subsequentStates.pop_back();
}

/*
void State::printState() {
    wprintf(L"\n");
    wprintf(L"   | ");

    char dimensions = board->getDimensions();

    for (char x = 0; x < dimensions; x++)
        wprintf(L"%02i ", x);

    wprintf(L"\n");
    wprintf(L"---+");
    for (char x = 0; x < dimensions; x++)
        wprintf(L"---");
    wprintf(L"\n");
    for (char x = 0; x < dimensions; x++) {
        wprintf(L"%02i |", x);
        for (char y = 0; y < dimensions; y++) {
            Space space = board->getSpace(x, y);

            if (space.getPiece().getColor() == Piece::BLACK)
                wprintf(L"-B-");
            //			wprintf(L"─●─");
            else if (space.getPiece().getColor() == Piece::WHITE)
                wprintf(L"-W-");
            //			wprintf(L"─○─");
            else
                wprintf(L"-+-");
        }
        wprintf(L"\n");
    }
    wprintf(L"\n");
}
*/

/*
* for each possible state
* 1. clone current board
* 2. ask board to place piece
*/
short State::generateSubsequentStates (bool color, unsigned char level)
{
    if (level > 0)
    {
        char dimensions = board->getDimensions();
        short subStatesGenerated = 0;

        #pragma omp parallel for reduction(+:subStatesGenerated)// default(none)
        for (char y = 0; y < dimensions; y++)
        {
            for (char x = 0; x < dimensions; x++)
            {
                if (board->getSpace (x, y).isEmpty() /*&& board.legalMove(color, i, j)*/)
                {
                    Board* newBoard = board->clone();
                    //Piece* newPiece = new Piece (color, x, y);
                    Piece* newPiece = new Piece (color, x, y);
                    newBoard->addPiece (newPiece);

                    //State subsequentState = State (newBoard);
                    State* subsequentState = new State (newBoard, color);
                    subStatesGenerated += subsequentState->generateSubsequentStates ( (color + 1) % 2, level - 1) + 1;

                    #pragma omp critical
                    subsequentStates.push_back (subsequentState);
                    //qDebug()  << "generated state" << y * dimensions + x << "at level" << QString::number(level);
                    //qDebug() << "new state generated at row" << QString::number(y) << "col" << QString::number(x);
                }
            }
        }
        return subStatesGenerated;
    }
    return 0;
}

State* State::subStateAt (unsigned short stateIdx)
{
    return subsequentStates[stateIdx];
}

State* State::subStateAtDeleteOthers (unsigned short stateIdx)
{
    swap(subsequentStates[0], subsequentStates[stateIdx]);

    #pragma omp parallel for //reduction(+:branchesDeleted)
    for (short state = subsequentStates.size(); state > 1; --state)
    {
        //if (state - 1 != stateIdx)
        delete subsequentStates[state - 1];
//        branchesDeleted++;
        //qDebug() << omp_get_thread_num() << " deleted branch " << state;
    }

    for (unsigned short state = subsequentStates.size(); state > 1; --state)
        //delete subsequentStates.back(),
        subsequentStates.pop_back();

    return subsequentStates[0];
}

short State::subStatesCount()
{
    return subsequentStates.size();
}

void State::generateSubsequentStatesAfterMove(unsigned char level)
{
    if(level > 1)
        for (vector<State*>::iterator it = subsequentStates.begin(); it != subsequentStates.end(); ++it)
            (*it)->generateSubsequentStatesAfterMove(level - 1);
    else
	{
		//short substate = 0;
        for (vector<State*>::iterator it = subsequentStates.begin(); it != subsequentStates.end(); ++it)
		{
            (*it)->generateSubsequentStates(color, level);
			//qDebug() << "generated substates for substates" << QString::number(substate);
			//substate++;
		}
	}
}