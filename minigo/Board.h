/*
 * Board.h
 *
 *  Created on: Nov 18, 2013
 *      Author: tiliska
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Space.h"
#include <vector>
#include "boost/ptr_container/serialize_ptr_vector.hpp"
#include <omp.h>

using std::vector;

//#include <iostream>
//
//#include <boost/preprocessor/punctuation/comma.hpp>
//#include <boost/preprocessor/control/iif.hpp>
//#include <boost/preprocessor/comparison/equal.hpp>
//#include <boost/preprocessor/stringize.hpp>
//#include <boost/preprocessor/seq/for_each.hpp>
//#include <boost/preprocessor/seq/size.hpp>
//#include <boost/preprocessor/seq/seq.hpp>
//
//#define DEFINE_ENUM(name, values)                               \
//  enum name {                                                   \
//    BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)          \
//  };                                                            \
//  const char* format_##name(name val) {                         \
//    switch (val) {                                              \
//      BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_FORMAT, , values)       \
//    default:                                                    \
//        return 0;                                               \
//    }                                                           \
//  }
//
//#define DEFINE_ENUM_VALUE(r, data, elem)                        \
//  BOOST_PP_SEQ_HEAD(elem)                                       \
//  BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(elem), 2),      \
//               = BOOST_PP_SEQ_TAIL(elem), )                     \
//  BOOST_PP_COMMA()
//
//#define DEFINE_ENUM_FORMAT(r, data, elem)             \
//  case BOOST_PP_SEQ_HEAD(elem):                       \
//  return BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem));

class Board
{
public:
    Board (unsigned char dimensions);
    Board (const Board &obj);
    virtual ~Board();
    Board& operator= (const Board& other);

    bool moveIsLegal (Piece::colors color, unsigned char x, unsigned char y);
    bool spaceIsEmpty (unsigned char x, unsigned char y);
    bool spaceIsSameColor (Piece::colors color, unsigned char x, unsigned char y);

    unsigned short piecesCount();
    unsigned short getNumWhitePieces();
    unsigned short getNumBlackPieces();
    unsigned short computeTerritory (Piece::colors color);
    unsigned char getDimensions();

    void addPiece (Piece* piece);
    Piece* pieceAt (unsigned short index);

private:
    unsigned char dimensions;

    boost::ptr_vector<Piece> pieces;
    boost::ptr_vector<Space> spaces;

    void initialize (unsigned char dimensions);
    bool chainWillBeCaptured (Piece::colors color, unsigned char x, unsigned char y);
    bool spaceIsHeldBy (Piece::colors color, unsigned char x, unsigned char y, bool* checkedCoordinates);
    bool outOfBounds (unsigned char x, unsigned char y);
	void printCheckedSpaces(bool* checkedCoordinates);
};

#endif /* BOARD_H_ */
