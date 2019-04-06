#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataManager.h"
#include "parameter_set.h"
#include "parameterset_widget.h"
#include "CalculationThread.h"
#include "Viewer.h"
#include "LeftDockWidget.h"

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

	if (left_widget_ != NULL)
		delete left_widget_;
	left_widget_ = NULL;


}

void MainWindow::init()
{
	data_manager_ = new DataManager();
	parameter_set_ = new ParameterSet();
	calculation_thread_ = new CalculationThread();
	parameter_set_widget_ = NULL;
	image_viewer_ = NULL;
	left_widget_ = new LeftDockWidget(this);
	
	first_data_manager_ = NULL;
	second_data_manager_ = NULL;

	isMatcherMode_ = false;
	isalgorithmChoosed_ = false;

	connect(calculation_thread_, SIGNAL(needToUpdateViewer()), this, SLOT(needToUpdateViewer()));
	connect(calculation_thread_, SIGNAL(setActionAndWidget(bool, bool)), this, SLOT(showActionAndWidget(bool, bool)));
}

void MainWindow::createActions()
{
	action_load_image_ = new QAction(QIcon("./resource/open.ico"), tr("Load Image"), this);
	action_load_image_->setStatusTip("Load Image.");
	connect(action_load_image_, SIGNAL(triggered()), this, SLOT(loadImage()));

	action_save_image_ = new QAction(QIcon("./resource/save.ico"), tr("Save Image"), this);
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




	// detect mode
	action_to_detect_mode_ = new QAction(tr("Detector Mode"), this);
	action_to_detect_mode_->setStatusTip("Change to Detector Mode");
	connect(action_to_detect_mode_, SIGNAL(triggered()), this, SLOT(changeToDetectMode()));


	// matcher mode
	action_to_matcher_mode_ = new QAction(tr("Matcher Mode"), this);
	action_to_matcher_mode_->setStatusTip("Change to Matcher Mode");
	connect(action_to_matcher_mode_, SIGNAL(triggered()), this, SLOT(changeToMatcherMode()));

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

	menu_mode_ = menuBar()->addMenu(tr("Mode"));
	menu_mode_->addAction(action_to_detect_mode_);
	menu_mode_->addAction(action_to_matcher_mode_);
	
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
	isalgorithmChoosed_ = true;
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
	image_viewer_ = new Viewer();
	connect(image_viewer_, SIGNAL(mouseClickPosition(int, int)), this, SLOT(showDescriptor(int, int)));
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

void MainWindow::showDescriptor(int x, int y)
{
	qDebug() << "(x, y) : (" << x << ", " << y << ")";
	std::vector<cv::KeyPoint> keypoints = data_manager_->getKeyPoints();
	if (keypoints.empty()) return;
	
	// compute all dist
	std::vector<double> dists;
	for (std::vector<cv::KeyPoint>::iterator it = keypoints.begin(); it != keypoints.end(); ++it) {
		double distance = std::powf((x - it->pt.x), 2) + std::powf((y - it->pt.y), 2);
		dists.push_back(distance);
	}
	// find argMin
	int min_idx = (std::min_element(dists.begin(), dists.end())) - dists.begin();
	qDebug() << (min_idx);
	qDebug() << "(x, y) : (" << keypoints[min_idx] .pt.x << ", " << keypoints[min_idx].pt.y << ")";
	
	// show nearest point descriptor;
	cv::KeyPoint nearest_piont = keypoints[min_idx];
	double min_dist = dists[min_idx];
	cv::Mat desc = data_manager_->getDescriptors();
	cv::Mat col;
	if (min_dist < 900 || min_dist < nearest_piont.size * 200) {
		
		col  = desc.row(min_idx);
		qDebug() << "cool";
		double maxValue;
		cv::minMaxLoc(col, 0, &maxValue, 0, 0);
		int histSize = col.cols;
		int hpt = col.cols / 2;
		cv::Mat vectorShow(col.cols, col.cols, CV_8UC3, cv::Scalar(0, 0, 0));

		for (int i = 0; i < histSize; i++) {
			float value = col.at<float>(i);
			int intensity = cv::saturate_cast<int>(value * 0.9*(hpt / maxValue));
			cv::line(vectorShow, cv::Point(i, histSize), cv::Point(i, histSize - intensity), cv::Scalar::all(255));
		}

		cv::imshow("show decriptor vector", vectorShow);
	} 
}

void MainWindow::changeToMatcherMode()
{
	first_data_manager_ = new DataManager();
	second_data_manager_ = new DataManager();
	qDebug() << "show leftDock Widget";
	connect(left_widget_, SIGNAL(setCurrToImage1()), this, SLOT(changeToDM1()));
	connect(left_widget_, SIGNAL(setCurrToImage2()), this, SLOT(changeToDM2()));

	addDockWidget(Qt::LeftDockWidgetArea, left_widget_);
	left_widget_->showWidget();
}

void MainWindow::changeToDetectMode()
{
	if (first_data_manager_ != NULL)
		delete first_data_manager_;
	first_data_manager_ = NULL;
	if (second_data_manager_ != NULL)
		delete second_data_manager_;
	second_data_manager_ = NULL;

	if (data_manager_ != NULL)
		delete data_manager_;
	data_manager_ = new DataManager();
	qDebug() << "change to detect mode 这个函数有待实现";
}

void MainWindow::changeToDM1()
{
	
	data_manager_ = first_data_manager_; 
	qDebug() << "DM has changed to DM1";

	if (isalgorithmChoosed_)
		calculation_thread_->initAlgorithm(data_manager_, parameter_set_);

	needToUpdateViewer();
}

void MainWindow::changeToDM2()
{
	data_manager_ = second_data_manager_; 
	qDebug() << "DM has changed to DM2";

	if (isalgorithmChoosed_)
		calculation_thread_->initAlgorithm(data_manager_, parameter_set_);

	needToUpdateViewer();
}



