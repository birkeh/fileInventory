#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "cmediainfo.h"

#include <QDir>
#include <QMimeType>

#include <QFile>
#include <QTextStream>

#include <QDebug>


cMainWindow::cMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::cMainWindow),
	  m_scanImages(true),
	  m_scanVideos(true)
{
	ui->setupUi(this);
}

cMainWindow::~cMainWindow()
{
	delete ui;
}

void cMainWindow::addFile(const QString& fileName)
{
	QMimeType	mimeType	= m_mimeDB.mimeTypeForFile(fileName);

	if((mimeType.name().startsWith("image") && m_scanImages) || (mimeType.name().startsWith("video") && m_scanVideos))
	{
		ui->statusbar->showMessage(fileName);
		qApp->processEvents();
		m_mediaInfoList.add(fileName);
	}
}

void cMainWindow::on_pushButton_clicked()
{
//	m_scanImages	= true;

	scan("E:\\Babs\\Photos 2013 bis jetzt", "c:\\Temp\\CSV\\Babs.csv");
	scan("C:\\Users\\birkeh\\OneDrive\\__MEDIA__", "c:\\Temp\\CSV\\OneDrive.csv");

	ui->statusbar->showMessage("done.", 5000);
	qApp->processEvents();
}

void cMainWindow::scan(const QString& dir, const QString& fileName)
{
	m_mediaInfoList.clear();
	scanDir(dir);
	writeFile(fileName);
}

void cMainWindow::scanDir(const QString& dir)
{
	QDir		d(dir);
	QStringList	files	= d.entryList(QDir::Files);

	for(int x = 0;x < files.count();x++)
		addFile(dir + "\\" + files[x]);

	QStringList	dirs	= d.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);

	for(int x = 0;x < dirs.count();x++)
		scanDir(dir + "\\" + dirs[x]);
}

void cMainWindow::writeFile(const QString& fileName)
{
	ui->statusbar->showMessage("writing...");
	qApp->processEvents();

	QStringList	keys	= m_mediaInfoList.keys();

	QFile		file(fileName);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream	out(&file);

		for(int x = 0;x < keys.count();x++)
		{
			if(x)
				out << ";";

			out << "\"" << keys[x] << "\"";
		}
		out << "\n";

		for(int x = 0;x < m_mediaInfoList.count();x++)
		{
			cMediaInfo*	lpMediaInfo	= m_mediaInfoList[x];

			for(int y = 0;y < keys.count();y++)
			{
				if(y)
					out << ";";

				out << "\"" << lpMediaInfo->value(keys[y]) << "\"";
			}
			out << "\n";
		}
		file.close();
	}
}
