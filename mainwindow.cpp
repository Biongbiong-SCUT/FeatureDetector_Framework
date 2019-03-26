#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataManager.h"
#include "parameter_set.h"
#include "parameterset_widget.h"
#include "CalculationThread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


	setWindowTitle("Feature Detector UI");
	setGeometry(640, 320, 400, 400);
	
	QVBoxLayout *layout_left_ = new QVBoxLayout;
	layout_left_->addStretch(2);
	layout_main_ = new QHBoxLayout;
	layout_main_->addLayout(layout_left_);

	layout_main_->setStretch(1, 1);
	this->centralWidget()->setLayout(layout_main_);

	init();
	createActions();
	createMenus();
	createToolBars();
}

MainWindow::~MainWindow()
{
    delete ui;

	closeWidget();

	if (calculation_thread_ != NULL)
		delete calculation_thread_;
	calculation_thread_ = NULL;

	if (data_manager_ != NULL)
		delete data_manager_;
	data_manager_ = NULL;

	if (parameter_set_ != NULL)
		delete parameter_set_;
	parameter_set_ = NULL;
}

void MainWindow::init()
{
	data_manager_ = new DataManager();
	parameter_set_ = new ParameterSet();
	calculation_thread_ = new CalculationThread();
	parameter_set_widget_ = NULL;
	image_viewer_ = NULL;

	connect(calculation_thread_, SIGNAL(needToUpdateViewer()), this, SLOT(needToUpdateViewer()));
	connect(calculation_thread_, SIGNAL(setActionAndWidget(bool, bool)), this, SLOT(showActionAndWidget(bool, bool)));
}

void MainWindow::createActions()
{
	action_load_image_ = new QAction(QIcon("../resource/open.ico"), tr("Load Image"), this);
	action_load_image_->setStatusTip("Load Image.");
	connect(action_load_image_, SIGNAL(triggered()), this, SLOT(loadImage()));

	action_save_image_ = new QAction(QIcon("../resource/save.ico"), tr("Save Image"), this);
	action_save_image_->setStatusTip("Save Image.");
	connect(action_save_image_, SIGNAL(triggered()), this, SLOT(saveImage()));

	action_exit_ = new QAction(this);
	action_exit_->setText("Exit");
	action_exit_->setStatusTip("Exit.");
	connect(action_exit_, SIGNAL(triggered()), this, SLOT(close()));

	// status action
	action_to_original_ = new QAction(this);
	action_to_original_->setText("Original Image");
	action_to_original_->setStatusTip("Show Original Image");
	connect(action_to_original_, SIGNAL(triggered()), this, SLOT(transToOriginal()));

	action_to_feature_ = new QAction(this);
	action_to_feature_->setText("Feature Image");
	action_to_feature_->setStatusTip("Show Feature Image");
	connect(action_to_feature_, SIGNAL(triggered()), this, SLOT(transToFeature()));

	action_sift_ = new QAction(tr("SIFT"), this);
	action_sift_->setStatusTip("Detect features using SIFT algorithm.");
	connect(action_sift_, SIGNAL(triggered()), this, SLOT(showSIFTWidget()));

	action_surf_ = new QAction(this);
	action_orb_ = new QAction(this);
	action_frens_ = new QAction(this);
}

void MainWindow::createMenus()
{
	menu_file_ = menuBar()->addMenu(tr("File"));
	menu_file_->addAction(action_load_image_);
	menu_file_->addAction(action_save_image_);
	menu_file_->addSeparator();
	menu_file_->addAction(action_exit_);

	menu_algorithms_ = menuBar()->addMenu(tr("Algorithms"));
	menu_algorithms_->addAction(action_sift_);
	menu_algorithms_->addAction(action_surf_);
	menu_algorithms_->addAction(action_orb_);
	menu_algorithms_->addAction(action_frens_);
	menu_algorithms_->setEnabled(false);
}

void MainWindow::createToolBars()
{
	toolbar_file_ = addToolBar(tr("File"));
	toolbar_file_->addAction(action_load_image_);
	toolbar_file_->addAction(action_save_image_);

	toolbar_status_ = addToolBar(tr("Status"));
	toolbar_status_->addAction(action_to_original_);
	toolbar_status_->addAction(action_to_feature_);
	toolbar_status_->setEnabled(false);
}

void MainWindow::createStatusBar()
{
	statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
	label_operation_info_ = new QLabel();
	label_operation_info_->setAlignment(Qt::AlignCenter);
	label_operation_info_->setMinimumSize(label_operation_info_->sizeHint());

	statusBar()->addWidget(label_operation_info_);
	connect(calculation_thread_, SIGNAL(statusShowMessage(QString)), label_operation_info_, SLOT(setText(QString)));
}

void MainWindow::closeWidget()
{
	if (parameter_set_widget_ != NULL)
		delete parameter_set_widget_;
	parameter_set_widget_ = NULL;
}

void MainWindow::showWidget()
{
	calculation_thread_->initAlgorithm(data_manager_, parameter_set_);
	parameter_set_widget_ = new ParameterSetWidget(this, parameter_set_);

	connect(parameter_set_widget_, SIGNAL(ReadyToApply(QString)), this, SLOT(ApplyAlgorithm(QString)));
	addDockWidget(Qt::RightDockWidgetArea, parameter_set_widget_);
	parameter_set_widget_->showWidget();
}

void MainWindow::setActionStatus(bool value)
{
	action_load_image_->setEnabled(value);
	action_save_image_->setEnabled(value);

	menu_algorithms_->setEnabled(value);
	toolbar_status_->setEnabled(value);
}

void MainWindow::showImage()
{
	if (image_viewer_ != NULL) {
		delete image_viewer_;
		image_viewer_ = NULL;
	}
	cv::Mat image = data_manager_->getCurrentMat();
	QImage qimage = utils::cvMatToQImage(image);
	image_viewer_ = new QLabel();
	QPixmap pic = QPixmap::fromImage(qimage);
	if (pic.height() > 320) {
		pic = pic.scaledToHeight(320);
	}
	image_viewer_->setPixmap(pic);
	layout_main_->addWidget(image_viewer_);
	image_viewer_->show();
}



void MainWindow::loadImage()
{
	QString imageName = QFileDialog::getOpenFileName(this, tr("load Image"), "../images/", tr("*.png *.jpg *.jpeg *.bmp"));
	if (imageName.isNull()) 
	{
		return;
	}
	data_manager_->loadImage(imageName.toStdString());

	// show image 
	showImage();
	// enable to apply algorithm
	setActionStatus(true);
}

void MainWindow::saveImage()
{
	QString imageName = QFileDialog::getSaveFileName(this, tr("Save Image"), "../images/", 
		tr(" PNG (*.png);;JPG (*.jpg);;JPEG (*.jpeg);;BMP (*.bmp)"));
	if (imageName.isNull())
	{
		return;
	}
	data_manager_->saveImage(imageName.toStdString());
}

void MainWindow::showSIFTWidget()
{
	calculation_thread_->algorithm_type_ = CalculationThread::kSIFT;
	closeWidget();
	showWidget();
}

void MainWindow::ApplyAlgorithm(QString algorithm_name)
{
	calculation_thread_->setAlgorithmName(algorithm_name);
	calculation_thread_->start();
}

void MainWindow::needToUpdateViewer()
{
	showImage();
}

void MainWindow::showActionAndWidget(bool value1, bool value2)
{
	setActionStatus(value1);

	if (parameter_set_widget_ != NULL && value2) {
		closeWidget();
		showWidget();
	}
}

void MainWindow::transToOriginal()
{
	data_manager_->currentToOriginalMat(); needToUpdateViewer();
}

void MainWindow::transToFeature()
{
	data_manager_->currentToFeatureMat(); needToUpdateViewer();
}


