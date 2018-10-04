#include "headers/saveManager.h"

void SaveManager::readName()
{
	QString val = reader.readElementText();

	curSave.name = val;
}

void SaveManager::readTime()
{
	while(reader.readNextStartElement())
	{
		if(reader.name() == "hh")
		{
			int val = reader.readElementText().toInt();
			curSave.time.hh = val;
		}
		else if(reader.name() == "mm")
		{
			int val = reader.readElementText().toInt();
			curSave.time.mm = val;
		}
		else if(reader.name() == "ss")
		{
			int val = reader.readElementText().toInt();
			curSave.time.ss = val;
		}
		else
		{
			reader.skipCurrentElement();
		}
	}
}

void SaveManager::readPath()
{
	QString val = reader.readElementText();

	curSave.path = val;
}

void SaveManager::readVolume()
{
	int val = reader.readElementText().toInt();

	curSave.volume = val;
}

void SaveManager::readSaveFile()
{
	QFile file(pathToFile);
	if(!file.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::critical(nullptr, "Error", "Unable to open save file", QMessageBox::Ok);
	}

	reader.setDevice(&file);

	if(reader.readNextStartElement())
	{
		if(reader.name() == "saveData")	//root of the XML
		{
			for(int i = 0; reader.readNextStartElement(); i++)
			{
				if(reader.name() == "timer")
				{
					while(reader.readNextStartElement())
					{

						if(reader.name() == "name")
						{
							readName();
						}
						else if(reader.name() == "time")
						{
							readTime();
						}
						else if(reader.name() == "audioPath")
						{
							readPath();
						}
						else if(reader.name() == "audioVolume")
						{
							readVolume();
						}
						else
						{
							reader.skipCurrentElement();
						}
					}
				}
				else
				{
					reader.skipCurrentElement();
				}
				presets.push_back(curSave);
			}


		}
	}
	else
	{
		reader.raiseError(QObject::tr("Incorrect file"));
	}
	file.close();
}

void SaveManager::saveTimer(SaveData& timerData)
{
	writeStream.writeStartElement("timer");	//open timer element - the timer save
	writeStream.writeTextElement("name", timerData.name);

	writeStream.writeStartElement("time");	//open time element
	writeStream.writeTextElement("hh", QString::number(timerData.time.hh));
	writeStream.writeTextElement("mm", QString::number(timerData.time.mm));
	writeStream.writeTextElement("ss", QString::number(timerData.time.ss));
	writeStream.writeEndElement();	//close time element

	writeStream.writeTextElement("audioPath", timerData.path);
	writeStream.writeTextElement("audioVolume", QString::number(timerData.volume));

	writeStream.writeEndElement(); //close timer element - the timer save
}

void SaveManager::saveData()
{
	QFile file(pathToFile);
	if(!file.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::critical(nullptr, "Error", "Unable to open save file", QMessageBox::Ok);
	}
	file.resize(0);

	writeStream.setDevice(&file);
	writeStream.setAutoFormatting(true);

	writeStream.writeStartDocument();
	writeStream.writeStartElement("saveData");

	for(int i = 0; i < presets.size(); i++)
	{
		saveTimer(presets[i]);
	}

	writeStream.writeEndElement();
	writeStream.writeEndDocument();

	file.close();
}

void SaveManager::appendSave(QString& name, trip& time, QString& path, int& volume)	//ref input: name, timevalues, path, volume
{
	SaveData sd;
	sd.name = name;
	sd.time = time;
	sd.path = path;
	sd.volume = volume;

	appendSave(sd);
}

void SaveManager::appendSave(SaveData& timerData)
{
	presets.push_back(timerData);
}

void SaveManager::removePreset(int& index)
{
	if(index < presets.size())
	{
		presets.erase(presets.begin() + index);	
	}
	else
	{
		QMessageBox::critical(nullptr, "Error", "Vector index out of bounds", QMessageBox::Ok);
	}
}