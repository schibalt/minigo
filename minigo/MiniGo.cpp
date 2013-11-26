#include "MiniGo.h"
#include <QtGui\QPainter>
#include <QtGui\QPaintEvent>

#define SCENEWIDTHOFFSET 3

MiniGo::MiniGo (QWidget *parent)
    : QMainWindow (parent)
{
    ui.setupUi (this);
}

MiniGo::~MiniGo()
{
    /*
    delete initialState;*/
}

void MiniGo::passInitialState (State* initialState)
{
    this->initialState = initialState;

    this->initialState = initialState->stateAt (0);
}

void MiniGo::paintEvent (QPaintEvent *e)
{
    int dimensions = initialState->board->getDimensions();
    int viewWidth = ui.graphicsView->width() - SCENEWIDTHOFFSET; //offset
    int cellDim = viewWidth / (dimensions + 1);
    cellDim += 1; //because of the integer division in the previous line

    //print lines
    for (int line = dimensions; line > 0; --line)
    {
        ui.graphicsView->scene()->addLine (cellDim * line, 0, cellDim * line, viewWidth);
        ui.graphicsView->scene()->addLine (0, cellDim * line, viewWidth, cellDim * line);
    }

    int pieceRad = cellDim - (viewWidth / 100);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);

    //print pieces
    for (int piece = initialState->board->piecesCount(); piece > 0; --piece)
    {
        Piece pieceObj = initialState->board->pieceAt (piece - 1);
        int x = pieceObj.point.x + 1, y = pieceObj.point.y + 1;

		brush.setColor(pieceObj.getColor() + 2);

        ui.graphicsView->scene()->addEllipse (cellDim * x - pieceRad / 2, cellDim * y - pieceRad / 2, pieceRad, pieceRad, QPen(), brush);
    }
}