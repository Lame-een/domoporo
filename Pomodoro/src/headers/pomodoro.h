#pragma once
#include <QMainWindow>
#include <QInputDialog>
#include <QFileDialog>
#include "ui_pomodoro.h"
#include "timer.h"
#include "saveManager.h"

class Pomodoro : public QMainWindow
{
	Q_OBJECT

private:
	bool collapsed = false;

public:
	Pomodoro(QWidget *parent = Q_NULLPTR);

	void initTimer();
	void initCombo();

public slots:
	void startTimer();
	void pauseTimer();
	void stopTimer();
	void setTimer();

	void selectAudio();
	void setVolume(int);

	void qtAbout();
	void about();

	void loadPreset();
	void saveCurrent();
	void deletePreset();

	void collapse();
private:
	Ui::PomodoroClass ui;
	Timer LCDTimer;
	SaveManager sManager;
};
