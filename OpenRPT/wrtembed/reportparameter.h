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

#ifndef REPORTPARAMETER_H
#define REPORTPARAMETER_H

#include <QDialog>

#include "ui_reportparameter.h"
#include "parsexmlutils.h"
#include "mqlutil.h"
#include "querysource.h"

class ReportParameter : public QDialog, public Ui::ReportParameter
{
    Q_OBJECT

public:
    ReportParameter(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ReportParameter();
private:
  QuerySourceList* qsList;
  QString _mode;
  QMap<QString,ORParameter> *_map;

public slots:
    virtual QString paramName();
    virtual ORParameter paramData();
    virtual void setParamData( const ORParameter & param );
    virtual void sSelectionChanged();
    virtual void sAdd();
    virtual void sEdit();
    virtual void sRemove();
    virtual void setQueryList( QuerySourceList* qlist );
    virtual void setMap(QMap<QString,ORParameter> *map);
    virtual void setMode(QString mode);
    virtual void populateMqlParams();
    virtual void sUpdateName();

protected slots:
    virtual void languageChange();

};

#endif // REPORTPARAMETER_H
