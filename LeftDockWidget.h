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
	void ApplyMatcher(QString);
	void setCurrToImage1();
	void setCurrToImage2();
	void setCurrToMattingImage();
	void setCurrToResultImage();

public slots:
	void OnDefaultClick()
	{
		qDebug() << " what is wrong with you?";
	};
	void OnApplyClick()
	{
		qDebug() << " what is your name?";
		qDebug() << combo_box_->currentText();
		emit ApplyMatcher(combo_box_->currentText());
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

	void OnBtn3Click()
	{
		emit setCurrToMattingImage();
		qDebug() << "btn 3 clicked!";
	}

	void OnBtn4Click()
	{
		emit setCurrToMattingImage();
		qDebug() << "btn 4 clicked!";
	}

private:
	QFrame *Frame_;
	QVBoxLayout *VBoxLayout_;
	QVBoxLayout *VBoxLayout_Setting_;
	QLabel *Label_;
	QComboBox *combo_box_;
};

