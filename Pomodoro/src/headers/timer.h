#pragma once

#include<chrono>
#include<thread>
#include<QLCDNumber>
#include<QString>
#include<QMessageBox>
#include "AudioPlayer.h"

typedef long long int lli;

class Timer
{
private:
	std::thread* tThread;
	
	bool running = false;
	bool zeroTimer = true;

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
	//object used to contain and play the alarm
	AudioPlayer player;

	//timer name used for saves
	QString name = "defName";

	//pointers to the segments of the LCDDiplay
	QLCDNumber *hourDisp;
	QLCDNumber *minDisp;
	QLCDNumber *secDisp;

	//beginning values of the timer, used to save as a preset
	int setHour = 0;
	int setMin = 0;
	int setSec = 0;

	void setTime(std::string);
	void setTime(int, int, int);	//function to set the display, save values and reset the timer
	void getTime();
	
	void setDisplay(int, int, int);    //handles the LCD display values

	void pauseTimer();
	void stopTimer();
	void startTimer();
	void timerExec();    //worker thread which calculates the time left

	void endThread();
};