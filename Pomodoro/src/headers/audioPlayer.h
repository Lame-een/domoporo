#pragma once

#include <QMediaPlayer>
#include <QString>

class AudioPlayer
{
private:
	QString path;
	QMediaPlayer player;
	int volume;


public:
	AudioPlayer()
	{
		setAudio("C:\\DEV\\Qt\\Pomodoro\\Pomodoro\\data\\alarms\\oth_def.wav");
	}
	~AudioPlayer()
	{
	}

public slots:
	void setAudio(QString);
	QString getPath();
	void playAudio();
	void stopAudio();
	void setVolume(int);
};