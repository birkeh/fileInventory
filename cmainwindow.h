#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cmediainfo.h"

#include <QMainWindow>
#include <QMimeDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class cMainWindow; }
QT_END_NAMESPACE


class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	cMainWindow(QWidget *parent = nullptr);
	~cMainWindow();

private:
	Ui::cMainWindow*	ui;
	cMediaInfoList		m_mediaInfoList;
	QMimeDatabase		m_mimeDB;
	bool				m_scanImages;
	bool				m_scanVideos;

	void				scan(const QString& dir, const QString& fileName);

	void				addFile(const QString& fileName);
	void				scanDir(const QString& dir);
	void				writeFile(const QString& fileName);

private slots:
	void on_pushButton_clicked();
};
#endif // CMAINWINDOW_H
