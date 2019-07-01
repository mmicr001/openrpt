/*
 * This file is part of the OpenRPT report writer and rendering engine,
 * and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple,
 * portions are Copyright (C) 2012 by Paladin Logic, Ltd.  It
 * is licensed to you under the xTuple End-User License Agreement ("the
 * EULA"), the full text of which is available at www.xtuple.com/EULA.
 * While the EULA gives you access to source code and encourages your
 * involvement in the development process, this Package is not free
 * software.  By using this software, you agree to be bound by the
 * terms of the EULA.
 */

#ifndef LABELDEFINITIONS_H
#define LABELDEFINITIONS_H

#include <QDialog>

#include "ui_labeldefinitions.h"

class LabelDefinitions : public QDialog, public Ui::LabelDefinitions
{
    Q_OBJECT

public:
    LabelDefinitions(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~LabelDefinitions();

public slots:
    virtual void editLabelDef( QListWidgetItem * );
    virtual void btnEdit_clicked();
    virtual void btnDelete_clicked();
    virtual void btnAdd_clicked();
    virtual void init();
    virtual void sEnableButtons();

protected slots:
    virtual void languageChange();

};

#endif // LABELDEFINITIONS_H
