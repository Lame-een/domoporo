#pragma once
#include <QFile>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QString>

class AudioPlayer
{
private:
	QString path;
	QMediaPlayer player;

	QString defPath = ".\\data\\alarms\\oth_def.wav";

public:
	AudioPlayer()
	{
	}
	~AudioPlayer()
	{
	}
	int volume = 50;

public slots:
	void setAudio(QString);
	QString getPath();
	void playAudio();
	void stopAudio();
	void setVolume(int);
};