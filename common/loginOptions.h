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

#ifndef __LOGINOPTIONS_H__
#define __LOGINOPTIONS_H__

#include <QDialog>

#include "parameter.h"

#include "tmp/ui_loginOptions.h"

class loginOptions : public QDialog, public Ui::loginOptions
{
    Q_OBJECT

public:
    loginOptions(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WFlags fl = 0);
    ~loginOptions();

    QString _databaseURL;

public slots:
    virtual void set( const ParameterList & pParams );

protected slots:
    virtual void languageChange();

    virtual void sSave();


};

#endif // LOGINOPTIONS_H
