#include "MiniGo.h"
#include <QtGui\QPainter>
#include <QtGui\QPaintEvent>
#include <QMessagebox>
#include <QDebug>

#define SCENEWIDTHOFFSET 3

MiniGo::MiniGo (QWidget *parent)
    : QMainWindow (parent)
{
    ui.setupUi (this);
    ui.graphicsView->setScene (new QGraphicsScene (this));
    brush.setStyle (Qt::SolidPattern);
    pass = 0;
}

MiniGo::~MiniGo()
{
    delete primaryState;
}

void MiniGo::passInitialState (unsigned char dimensions, unsigned char plies)
{
    qDebug() << "size of board is" << sizeof(Board);

    this->plies = plies;

    primaryState = new State(dimensions, Piece::WHITE, plies);
    activeState = primaryState;
	updateListWidget();
}

void MiniGo::updateListWidget()
{
    ui.listWidget->clear();
    for (unsigned short stateIdx = 0; stateIdx < primaryState->subStatesCount(); ++stateIdx)
    {
        unsigned char x = primaryState->subStateAt (stateIdx).x, y = primaryState->subStateAt (stateIdx).y;
        ui.listWidget->addItem (QString::number(x) + ", " + QString::number(y));
    }
    ui.listWidget->setCurrentRow(0);
}

void MiniGo::paintEvent (QPaintEvent *e)
{
    ui.graphicsView->scene()->clear();
    unsigned char dimensions = activeState->getDimensions();
    float viewWidth = ui.graphicsView->width() - SCENEWIDTHOFFSET; //offset
    float cellDim = viewWidth / (dimensions + 1);
    cellDim;

    //print lines
    for (char line = dimensions; line > 0; --line)
    {
        ui.graphicsView->scene()->addLine (cellDim * line, 0, cellDim * line, viewWidth);
        ui.graphicsView->scene()->addLine (0, cellDim * line, viewWidth, cellDim * line);
    }

    short pieceRad = cellDim - (viewWidth / 100);

    //print pieces
    for (unsigned short piece = activeState->piecesCount(); piece > 0; --piece)
    {
        Piece pieceObj = activeState->pieceAt (piece - 1);
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
 /*   unsigned short row = ui.listWidget->currentIndex().row();

    if (activeState == &primaryState->subStateAt (row))
    {
        activeState = primaryState;
    }
    else
    {
        activeState = &primaryState->subStateAt (row);
    }*/
        activeState = primaryState;
}

void MiniGo::on_moveButton_clicked()
{
    if(primaryState->piecesCount() < primaryState->getDimensions() * primaryState->getDimensions())
    {
        unsigned short row = ui.listWidget->currentIndex().row();

        ui.statusBar->showMessage("Deleting obsolete states");
		
        primaryState = primaryState->releaseSubStateAt (row);
        activeState = primaryState;

        ui.statusBar->showMessage("Generating new ply");
		
        primaryState->generateSubsequentStatesAfterMove(plies - 1);

        ui.statusBar->showMessage("Move made");
		updateListWidget();
    }
    else
    {
        ui.statusBar->showMessage("No more moves!");
    }
}

void MiniGo::on_listWidget_currentItemChanged (QListWidgetItem * item)
{
	unsigned short row = ui.listWidget->currentIndex().row();

	if(row < primaryState->subStatesCount())
	{
    ui.statusBar->showMessage ("Item " + QString::number (row) + " selected");
        activeState = &primaryState->subStateAt (row);
		paintEvent(NULL);
	}
}

void MiniGo::on_passButton_clicked ()
{
    if(pass == 0)
	{
		//primaryState->changeColor();
        pass++;
	}
    else
    {
        QMessageBox::information(NULL, "arg one", "arg two");
        this->close();
    }
}