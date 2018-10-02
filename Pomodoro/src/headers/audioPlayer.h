#pragma once

#include <QMediaPlayer>
#include <QString>

class AudioPlayer
{
private:
	QString path;
	QMediaPlayer player;
	int volume = 100;


public:
	AudioPlayer()
	{
		setAudio("C:\\DEV\\Qt\\Pomodoro\\Pomodoro\\data\\alarms\\oth_def.wav");
	}
	~AudioPlayer()
	{
		//delete player;
	}

public slots:
	void setAudio(QString);
	void playAudio();
	void setVolume(int);
};