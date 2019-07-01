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

#ifndef SELECTMQL_H
#define SELECTMQL_H

#include <QWidget>
#include <QSqlTableModel>

#include "ui_selectmql.h"

class SelectMQL : public QWidget, public Ui::SelectMQL
{
    Q_OBJECT

  public:
    SelectMQL(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~SelectMQL();

    Q_INVOKABLE virtual int     grade()  const;
    Q_INVOKABLE virtual QString group()  const;
    Q_INVOKABLE virtual int     id()     const;
    Q_INVOKABLE virtual QString name()   const;
    Q_INVOKABLE virtual QString notes()  const;
    Q_INVOKABLE virtual QString query()  const;
    Q_INVOKABLE virtual QString schema();

  public slots:
    virtual void setId(int id);

  signals:
    void selectedQuery(int id);

  protected slots:
    virtual void languageChange();
    virtual void sAccepted();
    virtual void sPopulate();
    virtual void sRejected();

  private:
    QSqlTableModel *_model;
};

#endif // SELECTMQL_H
