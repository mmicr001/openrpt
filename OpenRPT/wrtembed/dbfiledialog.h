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

#ifndef DBFILEDIALOG_H
#define DBFILEDIALOG_H

#include <QVariant>
#include <QDialog>

#include "ui_dbfiledialog.h"

class DBFileDialog : public QDialog, public Ui::DBFileDialog
{
    Q_OBJECT

public:
    DBFileDialog(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DBFileDialog();

public slots:
    virtual int getId();
    virtual QString getName();
    virtual int getGrade();
    virtual QString getPackage();
    virtual QString getSource();
    virtual QString getNameById();
    virtual int getGradeById();
    virtual QString getPackageById();
    virtual void sGradeChanged( int );

protected slots:
    virtual void languageChange();

    virtual void sSelectedReport();
    virtual void sNameChanged( const QString & text );
    virtual void sPackageChanged( const QString & text );
    virtual void sNameGradePackageChanged();


};

#endif // DBFILEDIALOG_H
