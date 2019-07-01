/*
 * This file is part of the OpenRPT report writer and rendering engine,
 * and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple.  It
 * is licensed to you under the xTuple End-User License Agreement ("the
 * EULA"), the full text of which is available at www.xtuple.com/EULA.
 * While the EULA gives you access to source code and encourages your
 * involvement in the development process, this Package is not free
 * software.  By using this software, you agree to be bound by the
 * terms of the EULA.
 */

#include "documentview.h"
#include "documentscene.h"
#include "reportgridoptions.h"
#include "reportpageoptions.h"
#include "reporthandler.h"
#include "graphicsitems.h"
#include "graphicssection.h"

// common
#include <xsqlquery.h>

// qt
#include <QtGui>
#include <QScrollBar>
#include <QSqlError>
#include <QWheelEvent>

// images
#include <document.xpm>

DocumentView::DocumentView(DocumentScene * ds, QWidget * parent)
  : QGraphicsView(ds, parent)
{
  _ds = ds;
  verticalScrollBar()->setValue(verticalScrollBar()->minimum());
}


void DocumentView::wheelEvent(QWheelEvent * e)
{
  if(e->modifiers() & Qt::ControlModifier) {
      zoom(e->delta());
      e->accept();
      return;
  }

  // adjust event for smoother scrolling
  QWheelEvent adjustedEvent ( e->pos(), e->delta()/2, e->buttons(), e->modifiers(), e->orientation() );

  QGraphicsView::wheelEvent(&adjustedEvent);
  if(adjustedEvent.isAccepted()) {
      e->accept();        
  }
}


void DocumentView::zoom(int delta)
{
    if(_ds->scaledTo() > 4 && delta > 0)
        return;

    if(delta < 0)
    {
        if(_ds->scaledTo() < .25)
            return;

        if(verticalScrollBar()->maximum() <= verticalScrollBar()->minimum()
            && horizontalScrollBar()->maximum() <= horizontalScrollBar()->minimum())
            return; // no need to zoom in further, the document is already fully visible      
    }

    double zoom = 1.0 + (delta / 1000.0);

    scale(zoom, zoom);
    _ds->setScaledTo(_ds->scaledTo()* zoom);
}


void DocumentView::keyPressEvent ( QKeyEvent * event )
{
    switch(event->key())
    {
    case Qt::Key_Left:
        moveSelectedItems(-1,0, event->modifiers());
        break;
    case Qt::Key_Right:
        moveSelectedItems(1,0, event->modifiers());
        break;
    case Qt::Key_Up:
        moveSelectedItems(0,-1, event->modifiers());
        break;
    case Qt::Key_Down:
        moveSelectedItems(0,1, event->modifiers());
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}


void DocumentView::keyReleaseEvent ( QKeyEvent * event )
{
	switch(event->key())
	{
	case Qt::Key_Up:
	case Qt::Key_Down:
		_ds->updateSectionsOfMovedItems(event->modifiers());
		break;
	default:
		QGraphicsView::keyPressEvent(event);
	}
}


void DocumentView::moveSelectedItems (int x, int y, Qt::KeyboardModifiers keyModifiers)
{
    ReportGridOptions *rgo = _ds->gridOptions();
    QGraphicsItem *firstItem = NULL;
	QPointF lastPos;

    foreach(QGraphicsItem *item, items()) 
    {
        if(item->isSelected())
		{
			if(!firstItem)
			{
				firstItem = item;
				lastPos = item->scenePos();
			}
            QPointF p = item->pos();
            if(rgo && rgo->isSnap())
            {
                p += QPointF(x*100*rgo->xInterval(), y*100*rgo->yInterval());
                p = rgo->snapPoint(p);
            }
            else
            {
                p += QPointF(x, y);
            }
            item->setPos(p);
		}
    }

	if(firstItem) 
	{
		_ds->setModified(true);
		if(y != 0)
			_ds->setSectionsColors(firstItem, lastPos, firstItem->scenePos(), keyModifiers);
	}
}

