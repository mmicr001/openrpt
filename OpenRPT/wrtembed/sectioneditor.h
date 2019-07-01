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

#ifndef SECTIONEDITOR_H
#define SECTIONEDITOR_H

class DocumentScene;

#include <QDialog>

#include "ui_sectioneditor.h"

class SectionEditor : public QDialog, public Ui::SectionEditor
{
    Q_OBJECT

public:
    SectionEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~SectionEditor();

    void init( DocumentScene * scene );

public slots:
    virtual void btnAdd_clicked();
    virtual void btnEdit_clicked();
    virtual void btnRemove_clicked();
    virtual void btnMoveUp_clicked();
    virtual void btnMoveDown_clicked();
    virtual void cbReportHeader_toggled( bool yes );
    virtual void cbReportFooter_toggled( bool yes );
    virtual void cbHeadFirst_toggled( bool yes );
    virtual void cbHeadLast_toggled( bool yes );
    virtual void cbHeadEven_toggled( bool yes );
    virtual void cbHeadOdd_toggled( bool yes );
    virtual void cbFootFirst_toggled( bool yes );
    virtual void cbFootLast_toggled( bool yes );
    virtual void cbFootEven_toggled( bool yes );
    virtual void cbFootOdd_toggled( bool yes );
    virtual void cbHeadAny_toggled( bool yes );
    virtual void cbFootAny_toggled( bool yes );
    virtual void sEnableButtons();

protected:
    DocumentScene * scene;

protected slots:
    virtual void languageChange();

};

#endif // SECTIONEDITOR_H
