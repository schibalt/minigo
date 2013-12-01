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
    heuristic = NULL;
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
void State::generateSubsequentStates (bool color, unsigned char level)
{
    if (level > 0)
    {
        char dimensions = board->getDimensions();
        //short subStatesGenerated = 0;

        #pragma omp parallel for //reduction(+:subStatesGenerated)// default(none)
        for (char y = 0; y < dimensions; y++)
        {
            for (char x = 0; x < dimensions; x++)
            {
                if (board->getSpace (x, y).isEmpty() /*&& board.legalMove(color, i, j)*/)
                {
                    Board* newBoard = board->clone();
                    Piece* newPiece = new Piece (color, x, y);
                    newBoard->addPiece (newPiece);

                    State* subsequentState = new State (newBoard, color, level - 1);
                    //subStatesGenerated += subsequentState->generateSubsequentStates ( (color + 1) % 2, level - 1) + 1;

                    #pragma omp critical
                    subsequentStates.push_back (subsequentState);
                    qDebug()  << "generated state" << y * dimensions + x << "at level" << QString::number(level);
                    //qDebug() << "new state generated at row" << QString::number(y) << "col" << QString::number(x);
                }
            }
        }
        //return subStatesGenerated;
    }
    //return 0;
}

State& State::subStateAt (size_t stateIdx)
{
    return subsequentStates[stateIdx];//[stateIdx];
}

State* State::subStateAtDeleteOthers (size_t stateIdx)
{
 //   swap(subsequentStates[0], subsequentStates[stateIdx]);
	//
	//boost::ptr_vector<State>::iterator it;
	//for (it = subsequentStates.begin() + 1; it < subsequentStates.end();/*no iterator increment*/ )
 //       it = subsequentStates.erase(it);
	State * chosenState = subsequentStates.release(subsequentStates.begin() + stateIdx).release();;
	subsequentStates.release();
    return chosenState;
//    #pragma omp parallel for //reduction(+:branchesDeleted)
//    for (short state = subsequentStates.size(); state > 1; --state)
//    {
//        //if (state - 1 != stateIdx)
//        //subsequentStates.erase(subsequentStates.begin() + 1, subsequentStates.end());
////        branchesDeleted++;
//        //qDebug() << omp_get_thread_num() << " deleted branch " << state;
//    }

    for (unsigned short state = subsequentStates.size(); state > 1; --state)
        //delete subsequentStates.back(),
        subsequentStates.pop_back();

}

short State::subStatesCount()
{
    return subsequentStates.size();
}

void State::generateSubsequentStatesAfterMove(unsigned char level)
{
    if(level > 1)
		for (boost::ptr_vector<State>::iterator iter = subsequentStates.begin(); iter != subsequentStates.end(); ++iter)
			iter->generateSubsequentStatesAfterMove(level - 1);
    else
	{
		//short substate = 0;
        for (boost::ptr_vector<State>::iterator iter = subsequentStates.begin(); iter != subsequentStates.end(); ++iter)
        {
            iter->generateSubsequentStates(color, level);
			//qDebug() << "generated substates for substates" << QString::number(substate);
			//substate++;
		}
	}
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