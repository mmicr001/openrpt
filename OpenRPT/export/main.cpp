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

#include <stdlib.h>

#include <QCoreApplication>
#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlError>
#include <QTextStream>
#include <QSqlQuery>
#include <QVariant>
#include <QByteArray>
#include <dbtools.h>

#include "builtinSqlFunctions.h"

int main(int argc, char *argv[])
{
  QCoreApplication application(argc, argv);
  application.addLibraryPath(".");

  if (argc > 1)
  {
    QString databaseURL;
    QString username;
    QString passwd;
    QString arguments;

    for (int counter = 1; counter < argc; counter++)
    {
      arguments = QString(argv[counter]);

      if (arguments.startsWith("-databaseURL=", Qt::CaseInsensitive))
        databaseURL = arguments.right(arguments.length() - 13);
      else if (arguments.startsWith("-username=", Qt::CaseInsensitive))
        username = arguments.right(arguments.length() - 10);
      else if (arguments.startsWith("-passwd=", Qt::CaseInsensitive))
        passwd = arguments.right(arguments.length() - 8);
    }

    if (  (databaseURL != "") && (username != "") ) {
      QSqlDatabase db;
      QString      protocol;
      QString      hostName;
      QString      dbName;
      QString      port;

// Open the Database Driver
      db = databaseFromURL(databaseURL);
      if (!db.isValid())
      {
        printf("Could not load the specified database driver.\n");
        exit(-1);
      }

//  Try to connect to the Database
      bool valport = false;
      int iport = port.toInt(&valport);
      if(!valport) iport = 5432;
      db.setUserName(username);
      if(!passwd.isEmpty())
        db.setPassword(passwd);
      if (!db.open())
      {
        printf( "Host=%s, Database=%s, port=%s\n",
                hostName.toLatin1().data(),
                dbName.toLatin1().data(),
                port.toLatin1().data() );

        printf( "Could not log into database.  System Error: %s\n",
                db.lastError().text().toLatin1().data() );
        exit(-1);
      }
      QSqlQuery().exec(getSqlFromTag("fmt05", db.driverName()));	// MANU

      // first we need to determine if there is already a report in the database of the same
      // name and if so then we will perform an update instead of an insert
      QSqlQuery qry;
      qry.prepare(getSqlFromTag("fmt06", db.driverName()));			// MANU
      qry.exec();
      if(!qry.exec()) {
          QSqlError err = qry.lastError();
          printf("Error: %s\n\t%s\n", qPrintable( err.text() ),
                                    qPrintable( err.databaseText() ) );
          exit(-1);
      }
      QString fname;
      while(qry.next()) {
        fname = QString("%1-%2.xml").arg(qry.value(0).toString()).arg(qry.value(1).toString());
        fname.replace('/',"-");
        QFile file(fname);
        if(file.open(QIODevice::WriteOnly))
        {
          QTextStream stream( &file );
          stream << qry.value(2).toString();
          file.close();
        }
        else
          printf("Error: Could not open file %s: %s\n", fname.toLatin1().data(), file.errorString().toLatin1().data());
      }
    }
    else if (databaseURL == "")
      printf("You must specify a Database URL by using the -databaseURL= parameter.\n");
    else if (username == "")
      printf("You must specify a Database Username by using the -username= parameter.\n");
  }
  else
    printf( "Usage: exportrpt -databaseURL='$' -username='$' -passwd='$'\n");
  return 0;
}
