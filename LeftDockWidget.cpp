#include "LeftDockWidget.h"

LeftDockWidget::LeftDockWidget(QWidget *parent)
	:QDockWidget(parent)
{
	Frame_ = new QFrame;
	setWidget(Frame_);

	this->setStyleSheet("font-size:14px;");
	VBoxLayout_ = new QVBoxLayout;
	Frame_->setLayout(VBoxLayout_);
	this->setWindowTitle(tr("Matting Widget."));
	QGroupBox *GroupBox = new QGroupBox("Image");
	VBoxLayout_Setting_ = new QVBoxLayout(GroupBox);

	//add button for image
	//Label_ = new QLabel("Matting algorithm");
	//Label_->setWordWrap(true);
	//VBoxLayout_Setting_->addWidget(Label_);

	QRadioButton *btn_im1 = new QRadioButton(tr(" Image1"));
	QRadioButton *btn_im2 = new QRadioButton(tr(" Image2"));
	
	VBoxLayout_Setting_->addWidget(btn_im1);
	VBoxLayout_Setting_->addWidget(btn_im2);
	connect(btn_im1, SIGNAL(clicked()), this, SLOT(OnBtn1Click()));
	connect(btn_im2, SIGNAL(clicked()), this, SLOT(OnBtn2Click()));
	//add selector
	VBoxLayout_Setting_->setAlignment(Qt::AlignTop);
	VBoxLayout_->insertWidget(1, GroupBox);
	VBoxLayout_->setAlignment(Qt::AlignTop);
	Frame_->showNormal();
	Frame_->adjustSize();
	this->showNormal();
	this->adjustSize();

	QPushButton *apply = new QPushButton(tr("Apply"), this);
	connect(apply, SIGNAL(clicked()), this, SLOT(OnApplyClick()));
	VBoxLayout_->addWidget(apply);
	this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->hide();
}

LeftDockWidget::~LeftDockWidget()
{
}

void LeftDockWidget::showWidget()
{
	this->show();
}
