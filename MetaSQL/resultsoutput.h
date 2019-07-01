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

#ifndef RESULTSOUTPUT_H
#define RESULTSOUTPUT_H

#include <QDialog>

class QMenu;

#include "ui_resultsoutput.h"

class ResultsOutput : public QDialog, public Ui::ResultsOutput
{
    Q_OBJECT

  public:
    ResultsOutput(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ResultsOutput();

  public slots:
    virtual void copy();
    virtual void createContextMenu(const QPoint &p);

  protected slots:
    virtual void languageChange();

  private:
    QMenu *_menu;
    QAction *_copyAction;

};

#endif // RESULTSOUTPUT_H
