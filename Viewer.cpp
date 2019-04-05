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
	emit mouseClickPosition(ev->x(), ev->y());

}

void Viewer::mouseReleaseEvent(QMouseEvent * ev)
{
	
}
