#pragma once
#include <QMainWindow>
#include <QInputDialog>
#include <QFileDialog>
#include <QShortcut>
#include <QPushButton>
#include <QSlider>
#include "ui_pomodoro.h"
#include "timer.h"
#include "saveManager.h"

class Pomodoro : public QMainWindow
{
	Q_OBJECT

private:
	bool collapsed = false;
	const int c_windowWidth = 545;
	const int c_windowCollapsedHeight = 181;
	const int c_windowHeight = 299;

	int buttonAssignedIndex[3] = {0, 1, 2};

public:
	Pomodoro(QWidget *parent = Q_NULLPTR);

	void initTimer();
	void initSaves();
	bool getTimerStatus();

	QShortcut *pauseUnpauseShortcut = new QShortcut(QKeySequence("Space"), this);
public slots:
	void startTimer();
	void pauseTimer();
	void stopTimer();
	void setTimer();

	void selectAudio();
	void setVolume(int);

	void qtAbout();
	void about();

	//void loadPreset(); depreciated
	void assignPreset(int buttonIndex);
	void saveCurrent();
	void deletePreset();
	void loadAlarm(int buttonIndex);
	void displayToLCD(trip& time);

	void collapse();

private:
	Ui::PomodoroClass ui;
	Timer LCDTimer;
	SaveManager sManager;
};
