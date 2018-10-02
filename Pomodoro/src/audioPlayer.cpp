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
	path = in;
	player.setMedia(QUrl::fromLocalFile(path));
	player.setVolume(volume);
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