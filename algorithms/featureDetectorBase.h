#pragma once
#include "../DataManager.h"
#include "../parameter_set.h"
class FeatureDetectorBase
{
public:
	FeatureDetectorBase(DataManager *_data_manager, ParameterSet *_parameter_set);
	~FeatureDetectorBase() {};
	virtual void detect() = 0;
	virtual void initParameters() = 0;

public:
	DataManager *data_manager_;
	ParameterSet *parameter_set_;
};

