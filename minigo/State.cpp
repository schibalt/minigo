/*
* State.cpp
*
*  Created on: Nov 18, 2013
*      Author: tiliska
*/

#include "State.h"

State::State (unsigned char dimensions, bool color, unsigned char plies)
{
    Board* board = new Board (dimensions);
	
        uint64_t runstarttime = time::GetTimeMs64();
    initialize (board, color, plies);
	
        uint64_t runendtime = time::GetTimeMs64();
        uint64_t runtime = runendtime - runstarttime;
		
        qDebug() << "initial generation time" << runtime << "for" << plies << "plies dimension" << getDimensions();
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

    generateSubsequentStates ( (Piece::colors)((color + 1) % 2), plies);
}

State::~State()
{
    delete board;
}

void State::generateSubsequentStates (Piece::colors color, unsigned char level)
{
    if (level > 0)
    {
        unsigned char dimensions = board->getDimensions();
        short subStatesGenerated = 0;

        //generate possible subsequent states (in parallel)
        #pragma omp parallel for schedule(dynamic)//reduction(+:subStatesGenerated)// default(none)
        for (short y = 0; y < dimensions; y++)
        {
            for (short x = 0; x < dimensions; x++)
            {
                if (board->moveIsLegal (color, x, y))
                {
                    Board* newBoard = new Board(*board);
                    Piece* newPiece = new Piece (color, x, y);
                    newBoard->addPiece (newPiece);

                    State* subsequentState = new State (newBoard, color, level - 1);
                    subsequentState->makeMove (x, y);
                    //subStatesGenerated += subsequentState->generateSubsequentStates ( (color + 1) % 2, level - 1) + 1;
                    #pragma omp critical
                    subsequentStates.push_back (subsequentState);

                    subStatesGenerated++;
					//qDebug() << "thread" << omp_get_thread_num() << "x" << x << "y" << y << "level" << level;
                    //qDebug()  << "generated state" << y * dimensions + x << "at level" << QString::number(level);
                }//if
            }//x
        }//y
		short heuristic = NULL;
		if(hasAnySubsequentStates())
			heuristic = subsequentStates.front().blackPoints;
        for (boost::ptr_vector<State>::iterator iter = subsequentStates.begin(); iter != subsequentStates.end(); ++iter)
        {
            if (color == Piece::WHITE) //MIN
            {
                heuristic = MIN (iter->blackPoints, heuristic);
                //heuristic = MIN (iter->whitePoints, heuristic);
            }
            else
            {
                heuristic = MAX (iter->blackPoints, heuristic);
                //heuristic = MAX (iter->whitePoints, heuristic);
            }
        }
		blackPoints = heuristic;
    /*    qDebug() << subStatesGenerated << "subsequent states generated at level" << level;
		qDebug() << "thread" << omp_get_thread_num() << "at level" << level;*/
	}
    else //farthest ply ahead; compute heuristic
    {
        blackPoints = board->computeTerritory (Piece::BLACK);
        //whitePoints = ABS (board->computeTerritory (Piece::WHITE));
    }
}

State& State::subStateAt (size_t stateIdx)
{
    return subsequentStates[stateIdx];
}

State* State::releaseSubStateAt (size_t stateIdx)
{
    State * chosenState = subsequentStates.release (subsequentStates.begin() + stateIdx).release();
    //subsequentStates.release();
    return chosenState;
}

short State::subStatesCount()
{
    return subsequentStates.size();
}

void State::generateSubsequentStatesAfterMove (unsigned char level)
{
    //unsigned short gssamloops = 0;
    if (level > 1)
    {
#pragma omp parallel for
		for(int subStates = 0; subStates < subsequentStates.size(); subStates++)
			subStateAt(subStates).generateSubsequentStatesAfterMove(level - 1);

        //for (boost::ptr_vector<State>::iterator iter = subsequentStates.begin(); iter != subsequentStates.end(); ++iter)
        //{
        //    iter->generateSubsequentStatesAfterMove (level - 1);
        //    //gssamloops++;
        //}
    }
    else
    {
			this->generateSubsequentStates ( (Piece::colors)((color + 1) % 2), level);
       /* for (boost::ptr_vector<State>::iterator iter = subsequentStates.begin(); iter != subsequentStates.end(); ++iter)
        {
		}*/
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

Piece* State::pieceAt (unsigned short index)
{
    return board->pieceAt (index);
}

bool State::hasAnySubsequentStates()
{
    return subsequentStates.size() > 0;
}

void State::changeColor()
{
    throw;
}

void State::makeMove (unsigned char x, unsigned char y)
{
    this->x = x, this->y = y;
}