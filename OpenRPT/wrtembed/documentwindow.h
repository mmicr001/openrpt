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

#ifndef __DOCUMENTWINDOW_H__
#define __DOCUMENTWINDOW_H__

#include <QtGui>
#include <QMainWindow>

class DocumentScene;
class DocumentView;
class ReportGridOptions;
class ReportHandler;

//
// Class DocumentWindow
//
class DocumentWindow : public QMainWindow
{  
  Q_OBJECT

  friend class ReportHandler;

  public:
    DocumentWindow(bool newDoc, ReportGridOptions * rgo, ReportHandler * handler, QWidget * parent);

  public slots:
    virtual void setCaption();

  protected:
    virtual void closeEvent(QCloseEvent * e);

	ReportHandler * _handler;
    DocumentScene * _scene;
    DocumentView * _view;
};

#endif

