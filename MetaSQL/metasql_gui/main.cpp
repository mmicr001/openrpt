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

#include <QApplication>
#include <QTranslator>
#include <QSqlDatabase>
#include <QMessageBox>

#include <xsqlquery.h>
#include <dbtools.h>
#include <login.h>

#include <parameter.h>

#include "data.h"

#include "mqledit.h"

int main(int argc, char *argv[])
{
  QString username  = "";
  bool    haveUsername    = false;
  bool    haveDatabaseURL = false;
  OpenRPT::loggedIn       = false;

  OpenRPT::databaseURL = "";

#if defined Q_WS_WIN
  OpenRPT::name = QObject::tr("MetaSQL Editor for Windows");
#elif defined Q_WS_X11
  OpenRPT::name = QObject::tr("MetaSQL Editor for Linux");
#elif defined Q_WS_MAC
  OpenRPT::name = QObject::tr("MetaSQL Editor for OS X");
#else
  OpenRPT::name = QObject::tr("MetaSQL Editor");
#endif

  QApplication app(argc, argv);
  app.addLibraryPath(".");

  if (argc > 1)
  {
    haveUsername        = false;
    bool    havePasswd  = false;
    QString passwd      = "";

    for (int intCounter = 1; intCounter < argc; intCounter++)
    {
      QString argument(argv[intCounter]);

      if (argument.contains("-databaseURL=")) {
        haveDatabaseURL = true;
        OpenRPT::databaseURL    = argument.right(argument.length() - 13);
      }
      else if (argument.contains("-username="))
      {
        haveUsername = true;
        username     = argument.right(argument.length() - 10);
      }
      else if (argument.contains("-passwd="))
      {
        havePasswd = true;
        passwd     = argument.right(argument.length() - 8);
      }
      else if (argument.contains("-noAuth"))
      {
        haveUsername = true;
        havePasswd   = true;
      } 

    }

    if ( (haveDatabaseURL) && (haveUsername) && (havePasswd) )
    {

	  QSqlDatabase db = databaseFromURL(OpenRPT::databaseURL);
      if (!db.isValid())
      {
        QMessageBox::critical(0, QObject::tr("Can not load database driver"),
          QObject::tr("Unable to load the database driver. Please contact your systems administrator."));
        QApplication::exit(-1);
      }

      db.setUserName(username);
      db.setPassword(passwd);

      if (!db.open())
      {
        QMessageBox::critical(0, QObject::tr("Unable to connect to database"),
          QObject::tr("Unable to connect to the database with the given information."));
        QApplication::exit(-1);
      }
      else
        OpenRPT::loggedIn = true;
    }

  }

  OpenRPT::languages.installSelected();

  MQLEdit mainwin;
  mainwin.show();

  QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
  return app.exec();
}
