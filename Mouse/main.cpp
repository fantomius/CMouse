#include "MainProcess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CMainProccess process;
	return a.exec();
}
