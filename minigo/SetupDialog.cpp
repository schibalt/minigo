#include "SetupDialog.h"
#include "Piece.h"

Dialog::Dialog()
	: QDialog()
{
	ui.setupUi(this);
	//QObject::connect(this, SIGNAL(
}

Dialog::~Dialog(){

	delete initialState;
}

void Dialog::on_okButton_clicked(){

	goFirst = ui.goFirstBox->isChecked();
	dimensions = ui.dimensionsBox->value();
	min = ui.minMaxBox->currentIndex();
	plies = ui.plyBox->value();

	this->close();
	initialState = new State(dimensions);
	initialState->generateSubsequentStates(Piece::BLACK, plies);
	w.show();
}