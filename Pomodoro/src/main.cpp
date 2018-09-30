#include "headers/pomodoro.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Pomodoro w;
	w.show();
	return a.exec();
}
