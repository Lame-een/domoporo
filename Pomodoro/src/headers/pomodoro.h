#pragma once

#include <QMainWindow>
#include <QInputDialog>
#include <QFileDialog>
#include "ui_pomodoro.h"
#include "timer.h"

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

	void selectAudio();
	void setVolume(int);

	void qtAbout();
private:
	Ui::PomodoroClass ui;
	Timer* LCDTimer = nullptr;
};
