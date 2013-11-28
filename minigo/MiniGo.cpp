#include "MiniGo.h"
#include <QtGui\QPainter>
#include <QtGui\QPaintEvent>

#define SCENEWIDTHOFFSET 3

MiniGo::MiniGo (QWidget *parent)
    : QMainWindow (parent)
{
    ui.setupUi (this);
    ui.graphicsView->setScene (new QGraphicsScene (this));
}

MiniGo::~MiniGo()
{
    /*
    delete initialState;*/
}

void MiniGo::passInitialState (State* initialState)
{
    activeState = initialState;
    primaryState = initialState;

    for (int state = primaryState->subStatesCount(); state > 0; --state)
    {
        ui.listWidget->addItem ("Move " + QString::number (state) + " (" + QString::number (primaryState->subStateAt (state - 1)->heuristic) + ")");
    }
}

void MiniGo::paintEvent (QPaintEvent *e)
{
    int dimensions = activeState->board->getDimensions();
    float viewWidth = ui.graphicsView->width() - SCENEWIDTHOFFSET; //offset
    float cellDim = viewWidth / (dimensions + 1);
    cellDim;// += 1; //because of the integer division in the previous line

    //print lines
    for (int line = dimensions; line > 0; --line)
    {
        ui.graphicsView->scene()->addLine (cellDim * line, 0, cellDim * line, viewWidth);
        ui.graphicsView->scene()->addLine (0, cellDim * line, viewWidth, cellDim * line);
    }

    int pieceRad = cellDim - (viewWidth / 100);

    QBrush brush;
    brush.setStyle (Qt::SolidPattern);

    //print pieces
    for (int piece = activeState->board->piecesCount(); piece > 0; --piece)
    {
        Piece pieceObj = activeState->board->pieceAt (piece - 1);
        int x = pieceObj.point.x + 1, y = pieceObj.point.y + 1;

        brush.setColor (pieceObj.getColor() + 2);

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
    ui.graphicsView->setScene (new QGraphicsScene (this));
    if (activeState == primaryState->subStateAt (ui.listWidget->currentIndex().row()))
        activeState = primaryState;
    else
        activeState = primaryState->subStateAt (ui.listWidget->currentIndex().row());
}

void MiniGo::on_moveButton_clicked()
{
    primaryState = primaryState->subStateAtDeleteOthers (ui.listWidget->currentIndex().row());
    activeState = primaryState;
}

void MiniGo::on_listWidget_itemClicked (QListWidgetItem * item)
{
    ui.statusBar->showMessage ("Item " + QString::number (ui.listWidget->currentIndex().row()) + " selected");
}