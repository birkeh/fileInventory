#include "cmediainfo.h"
#include "MediaInfoDLL.h"

#include <QDebug>


using namespace MediaInfoDLL;


cMediaInfo::cMediaInfo()
{

}

bool cMediaInfo::fromFile(const QString& fileName)
{
	MediaInfo	info;

	if(!info.Open(fileName.toStdWString().c_str()))
		return(false);

	QString informString	= QString::fromStdWString(info.Inform());
	QStringList	list		= informString.split("\r\n");

	info.Close();

	QString	category;

	for(int x = 0;x < list.count();x++)
	{
		if(list[x].isEmpty())
			continue;

		if(list[x].length() < 41)
		{
			category	= list[x];
			if(category == "General")
				category = "_General";
			continue;
		}

		if(category == "_General" || category.startsWith("video", Qt::CaseInsensitive) || category.startsWith("audio", Qt::CaseInsensitive))
		{
			QString	key		= list[x].left(41).trimmed();
			QString	value	= list[x].mid(42).trimmed();

			m_values.insert(category + "|" + key, value);
		}
	}
	return(true);
}

QStringList cMediaInfo::keys()
{
	return(m_values.keys());
}

QString cMediaInfo::value(const QString& key)
{
	return(m_values.value(key));
}

cMediaInfoList::cMediaInfoList()
{
}


cMediaInfo* cMediaInfoList::add(const QString& fileName)
{
	cMediaInfo*	lpNew	= new cMediaInfo;
	append(lpNew);
	lpNew->fromFile(fileName);
	m_keyList.append(lpNew->keys());
	m_keyList.removeDuplicates();

	return(lpNew);
}

QStringList cMediaInfoList::keys()
{
	m_keyList.sort(Qt::CaseInsensitive);
	return(m_keyList);
}
