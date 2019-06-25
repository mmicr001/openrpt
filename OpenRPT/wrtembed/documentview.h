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

#ifndef __DOCUMENTVIEW_H__
#define __DOCUMENTVIEW_H__

#include <QtGui>
#include <QGraphicsView>

class DocumentScene;
class ReportGridOptions;
class ReportHandler;

//
// Class DocumentView
//
class DocumentView : public QGraphicsView
{
  Q_OBJECT
  public:
    DocumentView(DocumentScene * ds, QWidget * parent = 0);
    void zoom(int delta);

  protected:
    virtual void wheelEvent(QWheelEvent * e);
    virtual void keyPressEvent ( QKeyEvent * event );
	virtual void keyReleaseEvent ( QKeyEvent * event );

  private:    
    void moveSelectedItems (int x, int y, Qt::KeyboardModifiers keyModifiers);

    DocumentScene * _ds;
};

#endif

