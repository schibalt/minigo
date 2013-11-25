#include "SetupDialog.h"

Dialog::Dialog()
	: QDialog()
{
	ui.setupUi(this);
	//QObject::connect(this, SIGNAL(
}

Dialog::~Dialog(){}

void Dialog::on_okButton_clicked(){

	goFirst = ui.goFirstBox->isChecked();
	dimensions = ui.dimensionsBox->value();
	min = ui.minMaxBox->currentIndex();
	this->close();
	//initialState(
	w.show();
}