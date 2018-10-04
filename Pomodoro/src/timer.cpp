#include "headers/timer.h"

void Timer::pauseTimer()
{
	if(running)
	{
		running = false;
		initTime = timeLeft;
		endThread();
	}
}

void Timer::stopTimer()
{
	if(running)
	{
		running = false;
		setTime(setVals.hh, setVals.mm, setVals.ss);
		endThread();
	}
	else
	{
		setTime(setVals.hh, setVals.mm, setVals.ss);
	}
	player.stopAudio();
}

void Timer::setDisplay(int hh, int mm, int ss)
{
	if(hh < 10)
	{
		hourDisp->display("0" + QString::number(hh));
	}
	else
	{
		hourDisp->display(hh);
	}

	if(mm < 10)
	{
		minDisp->display("0" + QString::number(mm));
	}
	else
	{
		minDisp->display(mm);
	}

	if(ss < 10)
	{
		secDisp->display("0" + QString::number(ss));
	}
	else
	{
		secDisp->display(ss);
	}
}

void Timer::setTime(int hh, int mm, int ss)
{
	if(mm > 59 || ss > 59)
	{
		QMessageBox::critical(nullptr, "Err", "Invalid Time Format", QMessageBox::Ok);
	}
	else
	{
		setVals.hh = hh;
		setVals.mm = mm;
		setVals.ss = ss;
		setDisplay(hh, mm, ss);

		running = false;
		initTime = (hh * 3600 + mm * 60 + ss)*1000;
		
		if(initTime != 0)
		{
			setZero = false;
			zeroTimer = false;
		}
		else
		{
			setZero = true;
			zeroTimer = true;
		}

		timeLeft = initTime;
	}
}

void Timer::getTime()
{
	lli timeCpy = timeLeft;
	timeCpy /= 1000;
	int hh = timeCpy / 3600;
	timeCpy %= 3600;
	int mm = timeCpy / 60;
	timeCpy %= 60;
	int ss = timeCpy;

	setDisplay(hh, mm, ss);
}

trip Timer::getCurrTime()
{
	trip ret;
	lli timeCpy = timeLeft;
	timeCpy /= 1000;
	ret.hh = timeCpy / 3600;
	timeCpy %= 3600;
	ret.mm = timeCpy / 60;
	timeCpy %= 60;
	ret.ss = timeCpy;

	return ret;
}

void Timer::startTimer()
{
	if(zeroTimer && !setZero)
	{
		stopTimer();
		startTimer();
	}else if(!running)
	{
		running = true;
		startPoint = std::chrono::system_clock::now();

		//new pointer to a thread; used due to issues with stack crated threads not being cleared fast enough
		tThread = new std::thread(&Timer::timerExec, this);
	}
}

void Timer::endThread()
{
	if(tThread->joinable())
	{
		tThread->join();
		delete tThread;
	}
}

void Timer::timerExec()
{
	while(running)
	{
		curPoint = std::chrono::system_clock::now();
		execTime = std::chrono::duration_cast<std::chrono::milliseconds>(curPoint - startPoint).count();

		timeLeft = initTime - execTime;

		if(timeLeft < 100)
		{
			if(!zeroTimer) player.playAudio();
			zeroTimer = true;

			running = false;
			return;
		}

		getTime();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}