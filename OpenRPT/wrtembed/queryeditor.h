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

#ifndef QUERYEDITOR_H
#define QUERYEDITOR_H

#include <QDialog>

#include "ui_queryeditor.h"

class QueryEditor : public QDialog, public Ui::QueryEditor
{
    Q_OBJECT

  public:
    QueryEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~QueryEditor();

  protected slots:
    virtual void languageChange();

    virtual void keyPressEvent( QKeyEvent * e );
    virtual void mqlToggled(bool);
    virtual void groupEditTextChanged(const QString &);
    virtual void nameEditTextChanged(const QString &);

};

#endif // QUERYEDITOR_H
