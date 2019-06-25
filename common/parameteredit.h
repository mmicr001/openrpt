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

#ifndef PARAMETEREDIT_H
#define PARAMETEREDIT_H

#include <QDialog>
#include <QDomDocument>

#include "parameter.h"

#include "tmp/ui_parameteredit.h"


class ParameterEdit : public QWidget, public Ui::ParameterEdit
{
  Q_OBJECT

  public:
    ParameterEdit(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ParameterEdit();

    Q_INVOKABLE static  QDialog      *ParameterEditDialog(ParameterEdit *p, QWidget *parent = 0, Qt::WindowFlags f = Qt::Dialog);
    Q_INVOKABLE virtual ParameterList getParameterList();
    Q_INVOKABLE         bool          setDocument(const QDomDocument & doc);

  public slots:
    virtual void clear();

  protected:
    QMap<QString,QVariant> _params;

  protected slots:
    virtual void languageChange();

    virtual void newItem();
    virtual void edit();
    virtual void editItem(int row);
    virtual void editItemList();
    virtual void doubleClick(int row, int col);
    virtual void selectionChange();
    virtual void deleteItem();

private:
    void updateParam(const QString & name, const QVariant & value, bool active);

    QMap<QString, QList<QPair<QString,QString> > > _lists;

};

#endif // PARAMETEREDIT_H
