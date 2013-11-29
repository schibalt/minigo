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

using std::cout;
using std::endl;

State::State (char dimensions)
{
    Board* board = new Board (dimensions);
    initialize (board);
}

State::State (Board* preconstructedBoard)
{
    initialize (preconstructedBoard);
}

void State::initialize (Board* board)
{
    this->board = board;
    heuristic = NULL;
}

State::~State()
{
    delete board;

    for (vector<State*>::iterator it = subsequentStates.begin(); it != subsequentStates.end(); ++it)
        delete * (it);
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
short State::generateSubsequentStates (bool color, char level)
{
    if (level > 0)
    {
        char dimensions = board->getDimensions();
        short subStatesGenerated = 0;

        #pragma omp parallel for
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
                    State* subsequentState = new State (newBoard);
                    subStatesGenerated += subsequentState->generateSubsequentStates ( (color + 1) % 2, level - 1) + 1;
                    subsequentStates.push_back (subsequentState);
                }
            }
        }
        return subStatesGenerated;
    }
    return 0;
}

State* State::subStateAt (short stateIdx)
{
    return subsequentStates[stateIdx];
}

State* State::subStateAtDeleteOthers (short stateIdx)
{
    //this is n't hte right way to do this
    /*if (stateIdx < subsequentStates.size() - 1)
        subsequentStates.erase (subsequentStates.begin() + stateIdx + 1, subsequentStates.end());

    if (stateIdx > 0)
        subsequentStates.erase (subsequentStates.begin(), subsequentStates.begin() + stateIdx);*/

    #pragma omp parallel for
    for (short state = subsequentStates.size(); state > 0; --state)
    {
        //delete subsequentStates.back(), subsequentStates.pop_back();
        if (state - 1 != stateIdx)
            delete subsequentStates[state - 1];

        qDebug() << omp_get_thread_num() << " deleted branch " << state;
    }

    return subsequentStates[stateIdx];
}

short State::subStatesCount()
{
    return subsequentStates.size();
}

void State::clearSubStates()
{
    subsequentStates.clear();
}