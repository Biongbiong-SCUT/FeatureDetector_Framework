#pragma once
#include <qlabel.h>
class Viewer:
	public QLabel
{
	Q_OBJECT
public:
	Viewer();
	~Viewer();
	void mousePressEvent(QMouseEvent * ev);
	void mouseReleaseEvent(QMouseEvent *ev);
signals:
	void mouseClickPosition(int, int);
};

