#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_pomodoro.h"
#include "timer.h"
#include <QInputDialog>

class Pomodoro : public QMainWindow
{
	Q_OBJECT

public:
	Pomodoro(QWidget *parent = Q_NULLPTR);
	~Pomodoro()
	{
		delete LCDTimer;
	}

	void initTimer();

public slots:
	void startTimer();
	void pauseTimer();
	void stopTimer();
	void setTimer();

	void qtAbout();

private:
	Ui::PomodoroClass ui;
	Timer* LCDTimer = nullptr;
};
