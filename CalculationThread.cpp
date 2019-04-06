#include "CalculationThread.h"



CalculationThread::CalculationThread()
{
	feature_detector_ = NULL;
	algorithm_name_ = "";
}


CalculationThread::~CalculationThread()
{
	if (feature_detector_ != NULL)
		delete feature_detector_;
}

void CalculationThread::initAlgorithm(DataManager * _data_manager, ParameterSet * _parameter_set)
{
	if (feature_detector_ != NULL)
		delete feature_detector_;
	feature_detector_ = NULL;

	switch (algorithm_type_)
	{
	case kSIFT:
		feature_detector_ = new FeatureDetectorSIFT(_data_manager, _parameter_set);
		break;
	default:
		break;
	}
}

void CalculationThread::run()
{
	emit(statusShowMessage("Now applying algorithm --" + algorithm_name_ + "-- ..."));
	emit(setActionAndWidget(false, false));
	feature_detector_->detect();
	emit(setActionAndWidget(true, false));
	emit(statusShowMessage("Applying algorithm --" + algorithm_name_ + "-- done."));
	emit(needToUpdateViewer());
	//emit(needToUpdateViwer(false));
}

