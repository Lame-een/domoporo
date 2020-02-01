#include "headers/pomodoro.h"

Pomodoro::Pomodoro(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowIcon(QIcon(":/Pomodoro/domoPoro.ico"));
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
	connect(ui.deletePreset, &QPushButton::released, this, &Pomodoro::deletePreset);
	//connect(ui.loadPreset, &QPushButton::released, this, &Pomodoro::loadPreset); depreciated

	connect(ui.assignToAlarm1, &QPushButton::released, this, [this](){assignPreset(0);});
	connect(ui.assignToAlarm2, &QPushButton::released, this, [this](){assignPreset(1);});
	connect(ui.assignToAlarm3, &QPushButton::released, this, [this](){assignPreset(2);});

	connect(ui.loadAlarm1, &QPushButton::released, this, [this](){loadAlarm(0);});
	connect(ui.loadAlarm2, &QPushButton::released, this, [this](){loadAlarm(1);});
	connect(ui.loadAlarm3, &QPushButton::released, this, [this](){loadAlarm(2);});

	connect(ui.collapseButton, &QPushButton::released, this, &Pomodoro::collapse);

	connect(pauseUnpauseShortcut, &QShortcut::activated, this, [this]{getTimerStatus() ? pauseTimer() : startTimer();});

	connect(&LCDTimer, &Timer::displaySignal, this, [this]{displayToLCD(LCDTimer.currVals);});

	sManager.buttonArray = buttonAssignedIndex;

	initSaves();
	initTimer();
	if(!collapsed)
	{
		collapse();
	}
}

void Pomodoro::qtAbout()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void Pomodoro::about()
{
	QMessageBox::about(this, "About DomoPoro", "DomoPoro version 1.2.2\n\nDomoPoro is licensed under the GNU General Public License v3.0\n\n\n\n");
}

void Pomodoro::initTimer()
{
	//LCDTimer.hourDisp = ui.LCDhh;
	//LCDTimer.minDisp = ui.LCDmm;
	//LCDTimer.secDisp = ui.LCDss;

	loadAlarm(buttonAssignedIndex[0]);
	stopTimer();
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
	QString filename = QFileDialog::getOpenFileName(this, tr("Select alarm"), LCDTimer.player.getPath(), "All files (*.*);;MPEG-3 (*.mp3);;Microsoft Wave (*.wav)");
	LCDTimer.player.setAudio(filename);
}

void Pomodoro::setVolume(int in)
{
	ui.volumeValue->setText(QString::number(in));
	ui.volumeSlider->setValue(in);
	LCDTimer.player.setVolume(in);
}

void Pomodoro::initSaves()
{
	sManager.readSaveFile();

	for(int i = 0; i < sManager.presets.size(); i++)
	{
		ui.presetBox->addItem(sManager.presets[i].name, Qt::DisplayRole);
	}
}

void Pomodoro::loadAlarm(int buttonIndex)
{
	if(buttonIndex < 0 || buttonIndex > 2)
	{
		return;
	}
	int& index = buttonAssignedIndex[buttonIndex];

	if(index > sManager.presets.size() - 1 || index < 0)
	{
		LCDTimer.setTime(0, 0, 0);
	}
	else
	{
		trip& time = sManager.presets[index].time;

		LCDTimer.name = sManager.presets[index].name;
		LCDTimer.setTime(time.hh, time.mm, time.ss);
		LCDTimer.player.setAudio(sManager.presets[index].path);
		setVolume(sManager.presets[index].volume);

		ui.presetBox->setCurrentIndex(index);

		startTimer();
	}
}

void Pomodoro::assignPreset(int buttonIndex)
{
	int currIndex = ui.presetBox->currentIndex();
	if(currIndex >= 0)
	{
		buttonAssignedIndex[buttonIndex] = currIndex;
		sManager.saveData();
	}
}

/*
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
*/

void Pomodoro::saveCurrent()
{
	bool ok;
	QString name = QInputDialog::getText(this, "Timer name", "Enter timer name", QLineEdit::Normal, "Timer", &ok, Qt::MSWindowsFixedSizeDialogHint);

	if(ok)
	{
		trip timeVals = LCDTimer.getTime();
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
		this->resize(c_windowWidth, c_windowCollapsedHeight);
		collapsed = true;
	}
	else
	{
		this->resize(c_windowWidth, c_windowHeight);
		collapsed = false;
	}
}

bool Pomodoro::getTimerStatus()
{
	return LCDTimer.running;
}

void Pomodoro::displayToLCD(trip& time)
{
	QLCDNumber*& hhDisplay = ui.LCDhh;
	QLCDNumber*& mmDisplay = ui.LCDmm;
	QLCDNumber*& ssDisplay = ui.LCDss;
	if(time.hh < 10)
	{
		hhDisplay->display("0" + QString::number(time.hh));
	}
	else
	{
		hhDisplay->display(time.hh);
	}

	if(time.mm < 10)
	{
		mmDisplay->display("0" + QString::number(time.mm));
	}
	else
	{
		mmDisplay->display(time.mm);
	}

	if(time.ss < 10)
	{
		ssDisplay->display("0" + QString::number(time.ss));
	}
	else
	{
		ssDisplay->display(time.ss);
	}
}