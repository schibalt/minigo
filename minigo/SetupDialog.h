#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/qdialog.h>
#include "ui_SetupDialog.h"
#include "MiniGo.h"
#include "State.h"

class Dialog : public QDialog
{
	Q_OBJECT

public:
	Dialog();
	~Dialog();
	bool goFirst;
	int dimensions;
	bool min;

private:
	Ui::Dialog ui;
	MiniGo w;
	State* initialState;

	public slots:
		void on_okButton_clicked();
};

#endif // DIALOG_H
