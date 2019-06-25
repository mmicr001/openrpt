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

#ifndef PATHEDITOR_H
#define PATHEDITOR_H

#include <QVariant>
#include <QDialog>
#include <QPen>
#include "ui_patheditor.h"

class PathEditor : public QDialog, public Ui::PathEditor
{
    Q_OBJECT

public:
    PathEditor(QWidget* parent, QPen initPen, Qt::WindowFlags fl = 0);
    ~PathEditor();

    QPen pen() { return _pen; }

public slots:

    void _btnColor_clicked();

protected slots:
    virtual void languageChange();
    virtual void accept();

private:
    QPen _pen;

};

#endif // PATHEDITOR_H
