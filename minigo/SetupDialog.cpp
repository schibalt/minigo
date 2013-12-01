#include "SetupDialog.h"
#include "Piece.h"

Dialog::Dialog()
	: QDialog()
{
	ui.setupUi (this);
	//initialState = NULL;
	on_okButton_clicked();
}

Dialog::~Dialog()
{
	//delete initialState;
}

void Dialog::on_okButton_clicked()
{
	goFirst = ui.goFirstBox->isChecked();
	dimensions = ui.dimensionsBox->value();
	min = ui.minMaxBox->currentIndex();
	plies = ui.plyBox->value();

	this->close();

	//bool startingColor = Piece::BLACK;
	/*State initialState = State (13, startingColor);
	initialState.generateSubsequentStates (startingColor, plies);*/

	w.passInitialState (new State(19, Piece::WHITE, plies), plies);
	w.show();
	//w.on_moveButton_clicked();
}