#pragma once
#include<chrono>
#include<thread>
#include<QLCDNumber>
#include<QString>
#include<QMessageBox>
#include "AudioPlayer.h"
//#include "pomodoro.h"

typedef long long int lli;

struct trip
{
	int hh = 0;
	int mm = 0;
	int ss = 0;
};

class Timer : public QObject
{
	Q_OBJECT
private:
	std::thread* tThread;
	
	bool zeroTimer = true;
	bool setZero = true;

	std::chrono::system_clock::time_point startPoint;
	std::chrono::system_clock::time_point curPoint;

	lli initTime = 0;	//first time point in seconds used in the calculation of timeLeft
	lli execTime = 0;	//live point in seconds for the calculation of timeLeft
	lli timeLeft = 0;

public:
	~Timer()
	{
		pauseTimer();	//safety pause to kill the thread
	}

	bool running = false;

	//object used to contain and play the alarm
	AudioPlayer player;

	//timer name used for saves
	QString name = "defName";

	//beginning values of the timer, used to save as a preset
	trip setVals;
	trip currVals;

	void setTime(int, int, int);	//function to set the display, save values and reset the timer
	trip getTime();		//function which calculates the current time and signals the main class to display the time
	void displayTime();


	void pauseTimer();
	void stopTimer();
	void startTimer();
	void timerExec();    //worker thread which calculates the time left

	void endThread();

signals:
	void displaySignal();
};