#pragma once
//#include "timer.h"
#include <QXMLStreamReader>
#include <QXMLStreamWriter>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QMessageBox>
#include <vector>

struct SaveData
{
	QString name;
	int hh;
	int mm;
	int ss;
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

	QString pathToFile = ".\\data\\data.xml";

	SaveData curSave;

	QXmlStreamReader reader;
	QXmlStreamWriter writeStream;
public:
	void readSaveFile();
	void saveData();

	void appendSave(SaveData&);
	void appendSave(QString& name, int& hh, int& mm, int& ss, QString& path, int& volume);
	void appendSave(QString, int, int, int, QString, int);

	void removePreset(int&);
	void removePreset(int);

	std::vector<SaveData> presets;
};