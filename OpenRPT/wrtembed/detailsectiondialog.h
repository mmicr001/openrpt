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

#ifndef DETAILSECTIONDIALOG_H
#define DETAILSECTIONDIALOG_H

class ORGraphicsSectionDetail;

#include <QDialog>

#include "ui_detailsectiondialog.h"

class DetailSectionDialog : public QDialog, public Ui::DetailSectionDialog
{
    Q_OBJECT

public:
    DetailSectionDialog(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DetailSectionDialog();

    void setReportSectionDetail( ORGraphicsSectionDetail * gsd );

public slots:
    virtual void btnAdd_clicked();
    virtual void btnEdit_clicked();
    virtual void btnRemove_clicked();
    virtual void btnMoveUp_clicked();
    virtual void brnMoveDown_clicked();

protected:
    ORGraphicsSectionDetail * _gsd;

protected slots:
    virtual void languageChange();

};

#endif // DETAILSECTIONDIALOG_H
