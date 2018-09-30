#include "headers/pomodoro.h"
#include <QPushButton>

Pomodoro::Pomodoro(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.startButton, &QPushButton::released, this, &Pomodoro::startTimer);
	connect(ui.stopButton, &QPushButton::released, this, &Pomodoro::stopTimer);
	connect(ui.pauseButton, &QPushButton::released, this, &Pomodoro::pauseTimer);
	connect(ui.setButton, &QPushButton::released, this, &Pomodoro::setTimer);
	connect(ui.qtAbout, &QPushButton::released, this, &Pomodoro::qtAbout);
	
	initTimer();
}

void Pomodoro::qtAbout()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void Pomodoro::initTimer()
{
	LCDTimer = new Timer;
	LCDTimer->hourDisp = ui.LCDhh;
	LCDTimer->minDisp = ui.LCDmm;
	LCDTimer->secDisp = ui.LCDss;

	LCDTimer->setTime(0, 0, 0);
}

void Pomodoro::pauseTimer()
{
	LCDTimer->pause();
}

void Pomodoro::stopTimer()
{
	LCDTimer->stop();
}

void Pomodoro::startTimer()
{
	LCDTimer->startTimer();
}

void Pomodoro::setTimer()
{
	bool okH, okM, okS;
	int hour = QInputDialog::getInt(this, "Hour Input", "Enter the amount of hours:", 0, 0, 99, 1, &okH);
	int minute = QInputDialog::getInt(this, "Minute Input", "Enter the amount of minutes:", 0, 0, 59, 1, &okM);
	int second = QInputDialog::getInt(this, "Second Input", "Enter the amount of seconds:", 0, 0, 59, 1, &okS);

	if(okH && okM && okS)
	{
		LCDTimer->setTime(hour, minute, second);
	}
}