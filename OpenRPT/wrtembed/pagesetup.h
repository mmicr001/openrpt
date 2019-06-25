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

#ifndef PAGESETUP_H
#define PAGESETUP_H

#include <QDialog>
#include <QString>

#include "reportpageoptions.h"
#include "ui_pagesetup.h"

class PageSetup : public QDialog, public Ui::PageSetup
{
    Q_OBJECT

public:
    PageSetup(QWidget* parent = 0);
    ~PageSetup();

    static const char strLetter[];
    static const char strLegal[];
    static const char strA4[];
    static const char strCustom[];
    static const char strLabel[];

    void            setData(const ReportPageOptions& rpo);
    void            getData(ReportPageOptions& rpo);

public slots:
    void            onPaperSize(int idx);

protected slots:
    virtual void languageChange();

private:
    virtual void enableCustom( bool yes );
};

#endif // PAGESETUP_H
