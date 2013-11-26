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
#include <omp.h>

State::State(int dimensions) {

	Board* board = new Board(dimensions);
	initialize(board);
}

State::State(Board* preconstructedBoard) {

	initialize(preconstructedBoard);
}

void State::initialize(Board* board){

	this->board = board;
	heuristic = INT_MIN;
}

State::~State() {

	delete board;
	
	for (vector<State*>::iterator it = subsequentStates.begin(); it != subsequentStates.end(); ++it)
		delete *(it);
}

void State::printState() {
	wprintf(L"\n");
	wprintf(L"   | ");

	int dimensions = board->getDimensions();

	for (int x = 0; x < dimensions; x++)
		wprintf(L"%02i ", x);

	wprintf(L"\n");
	wprintf(L"---+");
	for (int x = 0; x < dimensions; x++)
		wprintf(L"---");
	wprintf(L"\n");
	for (int x = 0; x < dimensions; x++) {
		wprintf(L"%02i |", x);
		for (int y = 0; y < dimensions; y++) {
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

/*
* for each possible state
* 1. clone current board
* 2. ask board to place piece
*/
int State::generateSubsequentStates(int color, int level) {

	if(level > 0){

		int dimensions = board->getDimensions();
		int subStatesGenerated = 0;

		for (int y = 0; y < dimensions; y++) {

			for (int x = 0; x < dimensions; x++){

				if (board->getSpace(x, y).isEmpty() /*&& board.legalMove(color, i, j)*/) {

					Board* newBoard = board->clone();
					Piece* newPiece = new Piece(color, x, y);
					newBoard->addPiece(newPiece);

					State* subsequentState = new State(newBoard);
					subStatesGenerated = subsequentState->generateSubsequentStates((color + 1) % 2, level - 1) + 1;
					subsequentStates.push_back(subsequentState);
					
					//delete newBoard;
					//delete subsequentState;
				}
			}
		}
		return subStatesGenerated;
	}
	return 0;
}
