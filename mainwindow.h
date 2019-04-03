#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "utils.h"

class Viewer;
class DataManager;
class ParameterSet;
class ParameterSetWidget;
class CalculationThread;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
	void init();
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();

	void closeWidget();
	void showWidget();
	void setActionStatus(bool value);

	//image
	void showImage();

private slots:
	void loadImage();
	void saveImage();
	void showSIFTWidget();
	void ApplyAlgorithm(QString algorithm_name);
	void needToUpdateViewer();

	void showActionAndWidget(bool value1, bool value2);

	void transToOriginal();
	void transToFeature();
private:

	QMenu *menu_file_;
	QMenu *menu_algorithms_;
	
	QAction *action_load_image_;
	QAction *action_save_image_;
	QAction *action_exit_;

	/* algorithm */
	QAction *action_sift_;
	QAction *action_surf_;
	QAction *action_orb_;
	QAction *action_frens_;

	// render
	QAction *action_to_original_;
	QAction *action_to_feature_;

	// tool bar
	QToolBar *toolbar_file_;
	QToolBar *toolbar_status_;
	//QToolBar *toolbar_image_info_;
	QLabel *label_operation_info_;

	// viewer
	QHBoxLayout *layout_main_;
	Viewer *image_viewer_;

	// data
	cv::Mat *image_data_;
	DataManager *data_manager_;
	ParameterSet *parameter_set_;
	ParameterSetWidget *parameter_set_widget_;
	CalculationThread *calculation_thread_;
};

#endif // MAINWINDOW_H
