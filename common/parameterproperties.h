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

#ifndef PARAMETERPROPERTIES_H
#define PARAMETERPROPERTIES_H

#include <QDialog>

#include "tmp/ui_parameterproperties.h"

class ParameterProperties : public QDialog, public Ui::ParameterProperties
{
  Q_OBJECT

  public:
    ParameterProperties(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ParameterProperties();

    Q_INVOKABLE virtual bool            active();
    Q_INVOKABLE virtual QList<QVariant> list();
    Q_INVOKABLE virtual QString         name();
    Q_INVOKABLE virtual QVariant::Type  type();
    Q_INVOKABLE virtual QString         typeName();
    Q_INVOKABLE virtual QVariant        value();

  public slots:
    virtual void languageChange();
    virtual void editItem();
    virtual void deleteItem();
    virtual void moveItemUp();
    virtual void moveItemDown();
    virtual void newItem();
    virtual void setActive(bool p);
    virtual void setList(const QList<QVariant> &l);
    virtual void setName(QString p);
    virtual void setType(QString p);
    virtual void setType(QVariant::Type p);
    virtual void setValue(QVariant p);
};
#endif
