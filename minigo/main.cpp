#include "SetupDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Dialog s;
	s.show();
	//while(s.isVisible());
	return a.exec();
}
