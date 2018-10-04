#pragma once
#include "timer.h"
#include <QXMLStreamReader>
#include <QXMLStreamWriter>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QMessageBox>
#include <vector>

struct SaveData	//save data transport struct
{
	QString name;
	trip time;
	QString path;
	int volume;
};

class SaveManager
{
private:
	void readName();
	void readTime();
	void readPath();
	void readVolume();
	void saveTimer(SaveData&);

	QString pathToFile = ".\\data\\save.xml";

	SaveData curSave;

	QXmlStreamReader reader;
	QXmlStreamWriter writeStream;
public:
	void readSaveFile();
	void saveData();

	void appendSave(SaveData&);
	void appendSave(QString&, trip&, QString&, int&);

	void removePreset(int&);

	std::vector<SaveData> presets;
};