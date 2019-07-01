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

#ifndef IMPORTWINDOW_H
#define IMPORTWINDOW_H

#include <QMainWindow>

#include "ui_importwindow.h"

class ImportWindow : public QMainWindow, public Ui::ImportWindow
{
    Q_OBJECT

  public:
    ImportWindow(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ImportWindow();

  public slots:
    virtual void helpRefGuide();
    virtual void helpAbout();
    virtual void fileExit();
    virtual void sAdd();
    virtual void sRemove();
    virtual void sImport();

  protected:
    virtual void timerEvent( QTimerEvent * e );

  protected slots:
    virtual void languageChange();

    virtual void reportsDoubleClicked( QListWidgetItem * item );

  private:
    int _dbTimerId;

};

#endif // IMPORTWINDOW_H
