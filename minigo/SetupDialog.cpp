#include "SetupDialog.h"
#include "Piece.h"

Dialog::Dialog()
	: QDialog()
{
	ui.setupUi (this);
	initialState = NULL;
}

Dialog::~Dialog()
{
	delete initialState;
}

void Dialog::on_okButton_clicked()
{
	goFirst = ui.goFirstBox->isChecked();
	dimensions = ui.dimensionsBox->value();
	min = ui.minMaxBox->currentIndex();
	plies = ui.plyBox->value();

	this->close();

	bool startingColor = Piece::BLACK;
	initialState = new State (dimensions, startingColor);
	initialState->generateSubsequentStates (startingColor, plies);

	w.passInitialState (initialState, plies);
	w.show();
}