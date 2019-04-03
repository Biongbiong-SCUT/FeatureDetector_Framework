#pragma once

#include "algorithms/featureDetectorBase.h"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/core/core.hpp>

class FeatureDetectorSIFT : public FeatureDetectorBase 
{
public:
	FeatureDetectorSIFT(DataManager *_data_manger, ParameterSet *_parameter_set);
	~FeatureDetectorSIFT();
	void detect() override; 
	void initParameters() override;
private:
	cv::Ptr<cv::xfeatures2d::SiftFeatureDetector> detector;
};

