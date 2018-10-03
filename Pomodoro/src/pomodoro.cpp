#include <QPushButton>
#include <QSlider>
#include "headers/pomodoro.h"
#include "headers/saveManager.h"

Pomodoro::Pomodoro(QWidget *parent)
	: QMainWindow(parent)
{
	/*
	SaveManager sm;

	sm.readSaveFile();
	sm.appendSave("NAME", 0, 25, 0, "PATH", 50);
	//sm.removePreset(1);
	sm.saveData();

	for(int i = 0; i < sm.presets.size(); i++)
	{
		qDebug(qPrintable(sm.presets[i].name));
		qDebug(qPrintable(QString::number(sm.presets[i].hh)));
		qDebug(qPrintable(QString::number(sm.presets[i].mm)));
		qDebug(qPrintable(QString::number(sm.presets[i].ss)));
		qDebug(qPrintable(sm.presets[i].path));
		qDebug(qPrintable(QString::number(sm.presets[i].volume)));
	}
	*/

	ui.setupUi(this);

	connect(ui.startButton, &QPushButton::released, this, &Pomodoro::startTimer);
	connect(ui.stopButton, &QPushButton::released, this, &Pomodoro::stopTimer);
	connect(ui.pauseButton, &QPushButton::released, this, &Pomodoro::pauseTimer);
	connect(ui.setButton, &QPushButton::released, this, &Pomodoro::setTimer);

	connect(ui.audioSelectButton, &QPushButton::released, this, &Pomodoro::selectAudio);
	connect(ui.testAudio, &QPushButton::released, this, [this]{LCDTimer->player.playAudio();});

	connect(ui.qtAbout, &QPushButton::released, this, &Pomodoro::qtAbout);

	connect(ui.volumeSlider, &QSlider::valueChanged, this, [this]{setVolume(ui.volumeSlider->value());});	//lambda expression used to avoid declaring another function inside the Pomodoro class

	initTimer();
}

void Pomodoro::qtAbout()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void Pomodoro::initTimer()
{
	LCDTimer = new Timer;
	LCDTimer->hourDisp = ui.LCDhh;
	LCDTimer->minDisp = ui.LCDmm;
	LCDTimer->secDisp = ui.LCDss;

	LCDTimer->setTime(0, 25, 0);
	setVolume(50);
	ui.volumeSlider->setValue(50);
}

void Pomodoro::setTimer()
{
	bool okH, okM, okS;
	int hour = QInputDialog::getInt(this, "Hour Input", "Enter the amount of hours:", 0, 0, 99, 1, &okH);
	int minute = QInputDialog::getInt(this, "Minute Input", "Enter the amount of minutes:", 0, 0, 59, 1, &okM);
	int second = QInputDialog::getInt(this, "Second Input", "Enter the amount of seconds:", 0, 0, 59, 1, &okS);

	if(okH && okM && okS)
	{
		LCDTimer->setTime(hour, minute, second);
	}
}

void Pomodoro::pauseTimer()
{
	LCDTimer->pauseTimer();
}

void Pomodoro::stopTimer()
{
	LCDTimer->stopTimer();
}

void Pomodoro::startTimer()
{
	LCDTimer->startTimer();
}

void Pomodoro::selectAudio()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Select alarm"), LCDTimer->player.getPath(), "Microsoft Wave (*.wav);;MPEG-3 (*.mp3);;All files (*.*)");
	LCDTimer->player.setAudio(filename);
}

void Pomodoro::setVolume(int in)
{
	ui.volumeValue->setText(QString::number(in));
	LCDTimer->player.setVolume(in);
}