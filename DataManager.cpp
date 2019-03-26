#include "DataManager.h"



DataManager::DataManager()
{

}


DataManager::~DataManager()
{
}

bool DataManager::loadImage(std::string filename)
{
	try {
		current_mat_ = feature_mat_ = original_mat_ = cv::imread(filename);

	}catch(cv::Exception e) {
		return false;
	}
	return true;
}

bool DataManager::saveImage(std::string filename)
{
	return cv::imwrite(filename, feature_mat_);
}
