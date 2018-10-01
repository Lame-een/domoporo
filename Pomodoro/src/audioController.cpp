#include "headers/audioController.h"

void AudioController::playAudio()
{
	player.play();
}

void AudioController::setAudio(QString in)
{
	path = in;
	player.setMedia(QUrl::fromLocalFile(path));
}

void AudioController::setVolume(int vol)
{
	volume = vol;
	player.setVolume(volume);
}