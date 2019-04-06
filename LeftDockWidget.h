#pragma once
#include <qwidget.h>
#include <QWidget>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <qdebug.h>

#include <qradiobutton.h>

class LeftDockWidget :
	public QDockWidget
{
	Q_OBJECT
public:
	explicit LeftDockWidget(QWidget *parent);
	~LeftDockWidget();

	enum MatType
	{
		kRANSAC, kKDTree, kHash
	};

	void showWidget();
	
signals:
	void ApplyMatcher(QString _matcher_base_name);
	void setCurrToImage1();
	void setCurrToImage2();

public slots:
	void OnDefaultClick()
	{
		qDebug() << " what is wrong with you?";
	};
	void OnApplyClick()
	{
		qDebug() << " what is your name?";
	};
	void OnBtn1Click()
	{
		emit setCurrToImage1();
		qDebug() << "btn 1 clicked!";
	}
	void OnBtn2Click()
	{
		emit setCurrToImage2();
		qDebug() << "btn 2 clicked!";
	}

private:
	QFrame *Frame_;
	QVBoxLayout *VBoxLayout_;
	QVBoxLayout *VBoxLayout_Setting_;
	QLabel *Label_;
};

