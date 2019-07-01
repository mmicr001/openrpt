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

#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>

#include "ui_graphwindow.h"

class GraphWindow : public QMainWindow, public Ui::GraphWindow
{
    Q_OBJECT

public:
    GraphWindow(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~GraphWindow();

public slots:
    virtual void setColCount(int);
    virtual void setRowCount(int);
    virtual void _dataTable_valueChanged( int r, int s );
    virtual void _labelTable_valueChanged( int r, int s );
    virtual void _btnClear_clicked();
    virtual void init( bool haveDB );
    virtual void _btnSql_clicked();

protected:
    bool _noUpdate;

protected slots:
    virtual void languageChange();
};

#endif // GRAPHWINDOW_H
