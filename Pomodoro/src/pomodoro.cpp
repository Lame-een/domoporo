#include <QPushButton>
#include <QSlider>
#include "headers/pomodoro.h"
#include "headers/saveManager.h"

Pomodoro::Pomodoro(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.startButton, &QPushButton::released, this, &Pomodoro::startTimer);
	connect(ui.stopButton, &QPushButton::released, this, &Pomodoro::stopTimer);
	connect(ui.pauseButton, &QPushButton::released, this, &Pomodoro::pauseTimer);
	connect(ui.setButton, &QPushButton::released, this, &Pomodoro::setTimer);

	connect(ui.audioSelectButton, &QPushButton::released, this, &Pomodoro::selectAudio);
	connect(ui.testAudio, &QPushButton::released, this, [this]{LCDTimer.player.playAudio();});

	connect(ui.qtAbout, &QPushButton::released, this, &Pomodoro::qtAbout);
	connect(ui.aboutButton, &QPushButton::released, this, &Pomodoro::about);

	connect(ui.volumeSlider, &QSlider::valueChanged, this, [this]{setVolume(ui.volumeSlider->value());});	//lambda expression used to avoid declaring another function inside the Pomodoro class

	connect(ui.savePreset, &QPushButton::released, this, &Pomodoro::saveCurrent);
	connect(ui.loadPreset, &QPushButton::released, this, &Pomodoro::loadPreset);
	connect(ui.deletePreset, &QPushButton::released, this, &Pomodoro::deletePreset);

	connect(ui.collapseButton, &QPushButton::released, this, &Pomodoro::collapse);

	connect(pauseUnpauseShortcut, &QShortcut::activated, this, [this]{getTimerStatus() ? pauseTimer() : startTimer();});

	initCombo();
	initTimer();
}

void Pomodoro::qtAbout()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void Pomodoro::about()
{
	QMessageBox::about(this, "About DomoPoro", "LOREM IPSUM");
}

void Pomodoro::initTimer()
{
	LCDTimer.hourDisp = ui.LCDhh;
	LCDTimer.minDisp = ui.LCDmm;
	LCDTimer.secDisp = ui.LCDss;

	int volume;
	if(sManager.presets.size() > 0)
	{
		QString& name = sManager.presets[0].name;
		trip& time = sManager.presets[0].time;
		QString& path = sManager.presets[0].path;
		volume = sManager.presets[0].volume;

		LCDTimer.player.setAudio(path);
		LCDTimer.name = name;
		LCDTimer.setTime(time.hh, time.mm, time.ss);
	}
	else
	{
		LCDTimer.name = "defName";
		LCDTimer.setTime(0, 25, 0);

		volume = 50;
	}

	setVolume(volume);
	ui.volumeSlider->setValue(volume);
}

void Pomodoro::setTimer()
{
	bool okH, okM, okS;
	int hour = QInputDialog::getInt(this, "Hour Input", "Enter the amount of hours:", 0, 0, 99, 1, &okH, Qt::MSWindowsFixedSizeDialogHint);
	if(!okH)
	{
		return;
	}
	int minute = QInputDialog::getInt(this, "Minute Input", "Enter the amount of minutes:", 0, 0, 59, 1, &okM, Qt::MSWindowsFixedSizeDialogHint);
	if(!okM)
	{
		return;
	}
	int second = QInputDialog::getInt(this, "Second Input", "Enter the amount of seconds:", 0, 0, 59, 1, &okS, Qt::MSWindowsFixedSizeDialogHint);
	if(!okS)
	{
		return;
	}

	LCDTimer.setTime(hour, minute, second);
}

void Pomodoro::pauseTimer()
{
	LCDTimer.pauseTimer();
}

void Pomodoro::stopTimer()
{
	LCDTimer.stopTimer();
}

void Pomodoro::startTimer()
{
	LCDTimer.startTimer();
}

void Pomodoro::selectAudio()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Select alarm"), LCDTimer.player.getPath(), "Microsoft Wave (*.wav);;MPEG-3 (*.mp3);;All files (*.*)");
	LCDTimer.player.setAudio(filename);
}

void Pomodoro::setVolume(int in)
{
	ui.volumeValue->setText(QString::number(in));
	ui.volumeSlider->setValue(in);
	LCDTimer.player.setVolume(in);
}

void Pomodoro::initCombo()
{
	sManager.readSaveFile();

	for(int i = 0; i < sManager.presets.size(); i++)
	{
		ui.presetBox->addItem(sManager.presets[i].name, Qt::DisplayRole);
	}
}

void Pomodoro::loadPreset()
{
	int index = ui.presetBox->currentIndex();
	
	if(index < 0)
	{
		return;
	}

	trip& time = sManager.presets[index].time;

	LCDTimer.name = sManager.presets[index].name;
	LCDTimer.setTime(time.hh, time.mm, time.ss);
	LCDTimer.player.setAudio(sManager.presets[index].path);
	setVolume(sManager.presets[index].volume);
}

void Pomodoro::saveCurrent()
{
	bool ok;
	QString name = QInputDialog::getText(this, "Timer name", "Enter timer name", QLineEdit::Normal, "TEST", &ok, Qt::MSWindowsFixedSizeDialogHint);

	if(ok)
	{
		trip timeVals = LCDTimer.getCurrTime();
		sManager.appendSave(name, timeVals, LCDTimer.player.getPath(), LCDTimer.player.volume);
		sManager.saveData();
		ui.presetBox->addItem(name, Qt::DisplayRole);
		ui.presetBox->setCurrentIndex(sManager.presets.size() - 1);
	}
}

void Pomodoro::deletePreset()
{
	int index = ui.presetBox->currentIndex();

	if(index < 0)
	{
		return;
	}

	ui.presetBox->removeItem(index);
	sManager.removePreset(index);
	sManager.saveData();
}

void Pomodoro::collapse()
{
	if(!collapsed)
	{
		this->resize(551, 165);
		collapsed = true;
	}
	else
	{
		this->resize(551, 295);
		collapsed = false;
	}
}

bool Pomodoro::getTimerStatus()
{
	return LCDTimer.running;
}