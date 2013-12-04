#include "MiniGo.h"

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
    qDebug() << "size of state is" << sizeof(State);
    qDebug() << "size of piece is" << sizeof(Piece);
    qDebug() << "size of space is" << sizeof(Space);

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
			short blackpoints = primaryState->subStateAt (stateIdx).blackPoints;
        ui.listWidget->addItem (QString::number(x) + ", " + QString::number(y) + " (" + QString::number(blackpoints) + ")");
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
	for (unsigned short pieceIdx = 0; pieceIdx < activeState->piecesCount(); ++pieceIdx)
    {
        Piece* piece = activeState->pieceAt (pieceIdx);
        unsigned char x = piece->getX() + 1, y = piece->getY() + 1;
        //short x = pieceObj.getPoint().x + 1, y = pieceObj.getPoint().y + 1;

        brush.setColor (Qt::GlobalColor(piece->getColor() + 2));

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
		
        //uint64_t runstarttime = time::GetTimeMs64();

        primaryState = primaryState->releaseSubStateAt (row);
        activeState = primaryState;
	
        /*uint64_t runendtime = time::GetTimeMs64();
        uint64_t runtime = runendtime - runstarttime;*/
		
        //qDebug() << "deletion time" << runtime << "for" << plies << "plies dimension" << primaryState->getDimensions();

        ui.statusBar->showMessage("Generating new ply");
		
       uint64_t  runstarttime = time::GetTimeMs64();
		
        primaryState->generateSubsequentStatesAfterMove(plies);
	
        uint64_t runendtime = time::GetTimeMs64();
        uint64_t runtime = runendtime - runstarttime;
		
        qDebug() << "new ply generation time" << runtime << "for" << plies << "plies dimension" << primaryState->getDimensions();

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
        QMessageBox::information(NULL, "", "arg two");
        this->close();
    }
}