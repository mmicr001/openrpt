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

#ifndef REPORTPARAMETERLIST_H
#define REPORTPARAMETERLIST_H

#include <QDialog>

#include "ui_reportparameterlist.h"
#include "parsexmlutils.h"
#include "mqlutil.h"
#include "querylist.h"

class ReportParameterList : public QDialog, public Ui::ReportParameterList
{
    Q_OBJECT

public:
    ReportParameterList(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ReportParameterList();

    virtual void setList( QMap<QString, ORParameter> * m );
    virtual void setQueryList( QuerySourceList* qlist );

protected:
    QMap<QString,ORParameter> *_map;
    QuerySourceList* qsList;

protected slots:
    virtual void languageChange();

    virtual void sAdd();
    virtual void sEdit();
    virtual void sDelete();
    virtual void sEdit( QListWidgetItem * );
    virtual void sEnableButtons();

};

#endif // REPORTPARAMETERLIST_H
