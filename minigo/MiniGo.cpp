#include "MiniGo.h"
#include <QtGui\QPainter>
#include <QtGui\QPaintEvent>

#define SCENEWIDTHOFFSET 3

MiniGo::MiniGo (QWidget *parent)
    : QMainWindow (parent)
{
    ui.setupUi (this);
    ui.graphicsView->setScene (new QGraphicsScene (this));

    brush.setStyle (Qt::SolidPattern);
}

MiniGo::~MiniGo()
{
    //delete initialState;
}

void MiniGo::passInitialState (State* initialState, unsigned char plies)
{
    this->plies = plies;
    ui.listWidget->clear();
    this->initialState = initialState;
    activeState = initialState;
    primaryState = initialState;

    for (unsigned short state = primaryState->subStatesCount(); state > 0; --state)
    {
        ui.listWidget->addItem ("Move " + QString::number (state) + " (" + QString::number (primaryState->subStateAt (state - 1)->heuristic) + ")");
    }
    ui.listWidget->setCurrentRow(0);
}

void MiniGo::paintEvent (QPaintEvent *e)
{
    ui.graphicsView->scene()->clear();
    char dimensions = activeState->board->getDimensions();
    float viewWidth = ui.graphicsView->width() - SCENEWIDTHOFFSET; //offset
    float cellDim = viewWidth / (dimensions + 1);
    cellDim;// += 1; //because of the integer division in the previous line

    //print lines
    for (char line = dimensions; line > 0; --line)
    {
        ui.graphicsView->scene()->addLine (cellDim * line, 0, cellDim * line, viewWidth);
        ui.graphicsView->scene()->addLine (0, cellDim * line, viewWidth, cellDim * line);
    }

    short pieceRad = cellDim - (viewWidth / 100);

    //print pieces
    for (unsigned short piece = activeState->board->piecesCount(); piece > 0; --piece)
    {
        Piece pieceObj = activeState->board->pieceAt (piece - 1);
		unsigned char x = pieceObj.getX() + 1, y = pieceObj.getY() + 1;
        //short x = pieceObj.getPoint().x + 1, y = pieceObj.getPoint().y + 1;

        brush.setColor (Qt::GlobalColor(pieceObj.getColor() + 2));

        ui.graphicsView->scene()->addEllipse
        (
            cellDim * x - pieceRad / 2,
            cellDim * y - pieceRad / 2,
            pieceRad,
            pieceRad,
            QPen(),
            brush
        );
    }
}

void MiniGo::on_previewButton_clicked()
{
    unsigned short row = ui.listWidget->currentIndex().row();
    if (activeState == primaryState->subStateAt (row))
        activeState = primaryState;
    else
        activeState = primaryState->subStateAt (row);
}

void MiniGo::on_moveButton_clicked()
{
    unsigned short row = ui.listWidget->currentIndex().row();
	ui.statusBar->showMessage("Deleting obsolete states");
	primaryState = primaryState->subStateAtDeleteOthers (ui.listWidget->currentIndex().row());//, ui.progressBar);
	ui.statusBar->showMessage("Generating new ply");
	primaryState->generateSubsequentStatesAfterMove(plies - 1);
    //primaryState = primaryState->subStateAt(row);
    //primaryState->clearSubStates();
    activeState = primaryState;
}

void MiniGo::on_listWidget_itemClicked (QListWidgetItem * item)
{
    ui.statusBar->showMessage ("Item " + QString::number (ui.listWidget->currentIndex().row()) + " selected");
}