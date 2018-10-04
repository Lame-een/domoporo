#pragma once

#include <QMediaPlayer>
#include <QString>

class AudioPlayer
{
private:
	QString path;
	QMediaPlayer player;


public:
	AudioPlayer()
	{
		setAudio(".\\data\\alarms\\oth_def.wav");
	}
	~AudioPlayer()
	{
	}
	int volume;

public slots:
	void setAudio(QString);
	QString getPath();
	void playAudio();
	void stopAudio();
	void setVolume(int);
};