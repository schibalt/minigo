/*
 * Piece.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef PIECE_H_
#define PIECE_H_

class Piece {

public:
	Piece(int, int, int);
	virtual ~Piece();
	int getColor();
	static const int BLACK = 0;
	static const int WHITE = 1;
	Piece clone();

	class Point {

	private:
	protected:
	public:

		int x, y;
		Point() {
			x = -1;
			y = -1;
		}
		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}
		//int getX();
		//int getY();
	};

	Point point;
private:
	int color;
};

#endif /* PIECE_H_ */
