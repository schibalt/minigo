#ifndef MINIGO_H
#define MINIGO_H

#include <QtWidgets/QMainWindow>
#include "ui_MiniGo.h"

class MiniGo : public QMainWindow
{
	Q_OBJECT

public:
	MiniGo(QWidget *parent = 0);
	~MiniGo();

private:
	Ui::MiniGoClass ui;
};

#endif // MINIGO_H
