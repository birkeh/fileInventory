#ifndef CMEDIAINFO_H
#define CMEDIAINFO_H

#include <QString>
#include <QMap>
#include <QList>
#include <QStringList>

#include <QMetaType>


class cMediaInfo
{
public:
	cMediaInfo();

	bool		fromFile(const QString& fileName);
	QStringList	keys();

	QString		value(const QString& key);

private:
	QMap<QString, QString>	m_values;
};

Q_DECLARE_METATYPE(cMediaInfo*)

class cMediaInfoList : public QList<cMediaInfo*>
{
public:
	cMediaInfoList();

	cMediaInfo*		add(const QString& fileName);
	QStringList		keys();

private:
	QStringList		m_keyList;
	bool			m_pictures;
	bool			m_videos;
};

#endif // CMEDIAINFO_H
