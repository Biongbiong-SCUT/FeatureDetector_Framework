#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class DataManager
{
public:
	DataManager();
	~DataManager();
	bool loadImage(std::string filename);
	bool saveImage(std::string filename);

	cv::Mat getOriginalMat() { return original_mat_; };
	cv::Mat getFeatureMat() { return feature_mat_; };
	cv::Mat getCurrentMat() { return current_mat_; };

	std::vector<cv::KeyPoint> getKeyPoints() { return keypoints_; };
	void setFeatureImage(cv::Mat _feature_mat) { feature_mat_ = _feature_mat; };
	void setOrinalImage(cv::Mat _original_mat) { original_mat_ = _original_mat; };
	void setKeyPoints(std::vector<cv::KeyPoint> _keypoints) { keypoints_ = _keypoints; };
	void setCurrentMat(cv::Mat _current_mat) { current_mat_ = _current_mat; };
	
	void currentToOriginalMat() { current_mat_ = original_mat_; }
	void currentToFeatureMat() { current_mat_ = feature_mat_; }

private:
	cv::Mat original_mat_;
	cv::Mat feature_mat_;
	cv::Mat current_mat_;
	std::vector<cv::KeyPoint> keypoints_;
};

