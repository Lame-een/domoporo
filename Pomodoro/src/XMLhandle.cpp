#include "headers/XMLhandle.h"

//WILL BE USED FOR HANDLING THE SAVING OF TIMER PRESETS

/*

	QFile file(".\\data\\data.xml");
	if(!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << "Cannot read file" << file.errorString();
		exit(0);
	}

	QString ret;

	QXmlStreamReader reader(&file);

	if (reader.readNextStartElement()) {
		if (reader.name() == "root"){
			while(reader.readNextStartElement()){
				if(reader.name() == "childA"){
					QString s = reader.readElementText();
					qDebug(qPrintable(s));
				}
				else
					reader.skipCurrentElement();
			}
		}
		else
			reader.raiseError(QObject::tr("Incorrect file"));
	}

*/