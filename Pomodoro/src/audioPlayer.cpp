#include "headers/AudioPlayer.h"

void AudioPlayer::playAudio()
{
	player.play();
}

void AudioPlayer::setAudio(QString in)
{
	path = in;
	player.setMedia(QUrl::fromLocalFile(path));
}

void AudioPlayer::setVolume(int vol)
{
	volume = vol;
	player.setVolume(volume);
}