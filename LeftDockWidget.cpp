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
	QRadioButton *btn_im1 = new QRadioButton(tr(" Image1"));
	QRadioButton *btn_im2 = new QRadioButton(tr(" Image2"));
	
	VBoxLayout_Setting_->addWidget(btn_im1);
	VBoxLayout_Setting_->addWidget(btn_im2);

	
	//QGroupBox *GroupBox_result = new QGroupBox("Result");
	//QVBoxLayout *QVBox = new QVBoxLayout(GroupBox_result);
	QRadioButton *btn_im3 = new QRadioButton(tr(" Matting Image"));
	QRadioButton *btn_im4 = new QRadioButton(tr(" Result Image"));
	VBoxLayout_Setting_->addWidget(btn_im3);
	VBoxLayout_Setting_->addWidget(btn_im4);
	connect(btn_im1, SIGNAL(clicked()), this, SLOT(OnBtn1Click()));
	connect(btn_im2, SIGNAL(clicked()), this, SLOT(OnBtn2Click()));
	connect(btn_im3, SIGNAL(clicked()), this, SLOT(OnBtn3Click()));
	connect(btn_im4, SIGNAL(clicked()), this, SLOT(OnBtn4Click()));

	//add selector
	QLabel *text_label = new QLabel(tr("Preprocessing"));
	VBoxLayout_->addWidget(text_label);
	combo_box_ = new QComboBox();
	combo_box_ ->addItem(tr("RANSAC"));
	combo_box_ ->addItem(tr("kd-tree"));
	combo_box_ ->addItem(tr("hashing"));
	VBoxLayout_ ->addWidget(combo_box_);
	
	// set align 
	VBoxLayout_Setting_->setAlignment(Qt::AlignTop);
	VBoxLayout_->insertWidget(0, GroupBox);
	//VBoxLayout_->insertWidget(1, GroupBox_result);

	VBoxLayout_->setAlignment(Qt::AlignTop);
	Frame_->showNormal();
	Frame_->adjustSize();
	this->showNormal();
	this->adjustSize();

	QLabel *text_label_apply = new QLabel(tr("Matching Descriptors"));
	QPushButton *apply = new QPushButton(tr("Apply"), this);
	connect(apply, SIGNAL(clicked()), this, SLOT(OnApplyClick()));
	VBoxLayout_->addWidget(text_label_apply);
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
