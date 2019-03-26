#include "FeatureDetectorSIFT.h"

FeatureDetectorSIFT::FeatureDetectorSIFT(DataManager * _data_manger, ParameterSet * _parameter_set)
	: FeatureDetectorBase(_data_manger, _parameter_set)
{
	initParameters();
}

FeatureDetectorSIFT::~FeatureDetectorSIFT()
{
	delete dectector;
}

void FeatureDetectorSIFT::detect()
{
	// get parameters
	int nfeatures;					parameter_set_->getValue(QString("nfeatures"), nfeatures);
	int nOctave_layers;				parameter_set_->getValue(QString("nOctaveLayers"), nOctave_layers);
	double constrast_threshold;		parameter_set_->getValue(QString("constrastThreshold"), constrast_threshold);
	int edge_threshold;				parameter_set_->getValue(QString("edgeThreshold"), edge_threshold);
	double sigma;					parameter_set_->getValue(QString("sigma"), sigma);
	
	// detect 
	dectector = cv::xfeatures2d::SIFT::create(nfeatures, nOctave_layers, constrast_threshold, edge_threshold, sigma);
	std::vector<cv::KeyPoint> keypoints;
	cv::Mat input = data_manager_->getOriginalMat();
	cv::Mat output;

	// find interest point
	dectector->detect(input, keypoints);
	cv::drawKeypoints(input, keypoints, output);

	// set data manager
	data_manager_->setKeyPoints(keypoints);
	data_manager_->setFeatureImage(output);
	data_manager_->currentToFeatureMat();
}

void FeatureDetectorSIFT::initParameters()
{
	parameter_set_->removeAllParameter();
	// set parameter
	parameter_set_->addParameter(QString("nfeatures"), 0, QString("Features Num."), QString("The number of features by ranking."));
	parameter_set_->addParameter(QString("nOctaveLayers"), 3, QString("Octave Layers Num."), QString("The number of octave layers."), true, 1, 10);
	parameter_set_->addParameter(QString("constrastThreshold"), 0.04, QString("Threshold of Contrast."), QString("The Threshold used to filter out weak features"), true, 1.0e-8, 100.0);
	parameter_set_->addParameter(QString("edgeThreshold"), 10, QString("Threshold of Edge."), QString("The Threshold used to filter edge-like features"), true, 0, 100);
	parameter_set_->addParameter(QString("sigma"), 1.6, QString("The sigma value"), QString("The sigma of Gaussian applied to the input image at the octave #0."), true, 10e-9, 1e6);
	// set info 
	parameter_set_->setName(QString("Feature Detector SIFT"));
	parameter_set_->setLabel(QString("Feature Detector SIFT"));
	parameter_set_->setIntroduction(QString("Feature Detector SIFT -- Parameters"));
}
