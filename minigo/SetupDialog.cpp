#include "SetupDialog.h"

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
	//goFirst = ui.goFirstBox->isChecked();
	unsigned char dimensions = ui.dimensionsBox->value();
	//min = ui.minMaxBox->currentIndex();
	unsigned char plies = ui.plyBox->value();
	
	w.passInitialState (7, 2);
	//w.passInitialState (dimensions, plies);
	w.show();
	//w.on_moveButton_clicked();
}