#pragma once
#include <qthread.h>

#include "parameter_set.h"
#include "datamanager.h"
#include "algorithms/featureDetectorBase.h"
#include "algorithms/FeatureDetectorSIFT.h"
class CalculationThread :
	public QThread
{
	Q_OBJECT

public:
	CalculationThread();
	~CalculationThread();

	enum AlgorithmsType
	{
		kSIFT, kSURF, kORB, kFRENS
	};

	void initAlgorithm(DataManager *_data_manager, ParameterSet *_parameter_set);
	void setAlgorithmName(const QString algorithm_name) { algorithm_name_ = algorithm_name; }

	void run();
signals:
	void needToUpdateViewer();
	void statusShowMessage(QString message);
	void setActionAndWidget(bool, bool);
public:
	QString algorithm_name_;
	AlgorithmsType algorithm_type_;
	FeatureDetectorBase *feature_detector_;
};

