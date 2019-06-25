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

#ifndef QUERYLIST_H
#define QUERYLIST_H

class QuerySource;
class QuerySourceList;

#include <QDialog>

#include "ui_querylist.h"

class QueryList : public QDialog, public Ui::QueryList
{
    Q_OBJECT

public:
    QueryList(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~QueryList();

public slots:
    virtual void editQuery( QListWidgetItem * );
    virtual void btnEdit_clicked();
    virtual void btnDelete_clicked();
    virtual void btnAdd_clicked();
    virtual void init( QuerySourceList * );
    virtual void sEnableButtons();

protected:
    QuerySourceList * qsList;

protected slots:
    virtual void languageChange();

};

#endif // QUERYLIST_H
