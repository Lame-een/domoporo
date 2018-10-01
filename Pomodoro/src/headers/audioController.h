#pragma once

#include <QMediaPlayer>
#include <QString>

class AudioController
{
private:
	QString path;
	QMediaPlayer player;
	int volume = 100;


public:
	AudioController()
	{
		setAudio("C:\\DEV\\Qt\\Pomodoro\\Pomodoro\\data\\alarms\\oth_def.wav");
	}
	~AudioController()
	{
		//delete player;
	}

public slots:
	void setAudio(QString);
	void playAudio();
	void setVolume(int);
};