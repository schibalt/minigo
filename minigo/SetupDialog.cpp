#include "SetupDialog.h"
#include "Piece.h"

Dialog::Dialog()
	: QDialog()
{
	ui.setupUi (this);
	on_okButton_clicked();
}

Dialog::~Dialog()
{
}

void Dialog::on_okButton_clicked()
{
	goFirst = ui.goFirstBox->isChecked();
	dimensions = ui.dimensionsBox->value();
	min = ui.minMaxBox->currentIndex();
	plies = ui.plyBox->value();

	this->close();

	w.passInitialState (9, 1);
	w.show();
	//w.on_moveButton_clicked();
}