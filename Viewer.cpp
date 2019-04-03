#include "Viewer.h"

#include <qdebug.h>
#include <QMouseEvent>
Viewer::Viewer()
{
}


Viewer::~Viewer()
{
}

void Viewer::mousePressEvent(QMouseEvent * ev)
{
	qDebug() << "press";
}

void Viewer::mouseReleaseEvent(QMouseEvent * ev)
{
	qDebug() << "x: " << ev->x() << "y: " << ev->y();
}
