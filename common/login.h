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

#ifndef __LOGIN_H__
#define __LOGIN_H__

class QSplashScreen;

#include <QDialog>

#include "parameter.h"

#include "tmp/ui_login.h"

class login : public QDialog, public Ui::login
{
    Q_OBJECT

  public:
    login(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~login();

    QString _databaseURL;

    virtual int set( const ParameterList & pParams, QSplashScreen * pSplash );
    virtual void populateDatabaseInfo();
    virtual QString username();
    virtual QString password();

  public slots:
    virtual int set( const ParameterList & pParams );

  protected slots:
    virtual void languageChange();

    virtual void sLogin();
    virtual void sOptions();


  private:
    bool _captive;
    QSplashScreen *_splash;
    QString _cUsername;
    QString _cPassword;
};

#endif
