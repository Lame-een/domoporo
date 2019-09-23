#include "headers/AudioPlayer.h"

void AudioPlayer::playAudio()
{
	player.play();
}

void AudioPlayer::stopAudio()
{
	player.stop();
}

void AudioPlayer::setAudio(QString in)
{
	QFile file(in);
	if(file.exists())
	{
		player.setMedia(QUrl::fromLocalFile(in));
		player.setVolume(volume);
	}
	else if(in != "")
	{
		QMessageBox::critical(nullptr, "Error", "Media file in save not found.", QMessageBox::Ok);

		file.close();
		QFile file(in);
		if(file.exists())
		{
			player.setMedia(QUrl::fromLocalFile(defPath));
			player.setVolume(50);
		}
	}
}

void AudioPlayer::setVolume(int vol)
{
	volume = vol;
	player.setVolume(volume);
}

QString AudioPlayer::getPath()
{
	return path;
}