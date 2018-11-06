/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2018 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#include <stdlib.h>

#include <QCoreApplication>
#include <QString>
#include <QRegExp>
#include <QSqlDatabase>
#include <QVariant>
#include <QFile>
#include <QtXml>
#include <QSqlError>
#include <QTextStream>
#include "xsqlquery.h"

#include <dbtools.h>

#include "builtinSqlFunctions.h"

int main(int argc, char *argv[])
{
  QCoreApplication application(argc, argv);
  application.addLibraryPath(".");

  QTextStream out(stdout, QIODevice::WriteOnly);

  if (argc > 1)
  {
    QString databaseURL;
    QString username;
    QString passwd;
    QString arguments;

    QString xml_file = QString::null;
    int     report_grade = 0;
    QString package;

    for (int counter = 1; counter < argc; counter++)
    {
      QString arguments(argv[counter]);

      if (arguments.startsWith("-databaseURL=", Qt::CaseInsensitive))
        databaseURL = arguments.right(arguments.length() - 13);
      else if (arguments.startsWith("-username=", Qt::CaseInsensitive))
        username = arguments.right(arguments.length() - 10);
      else if (arguments.startsWith("-passwd=", Qt::CaseInsensitive))
        passwd = arguments.right(arguments.length() - 8);
      else if (arguments.startsWith("-f=", Qt::CaseInsensitive))
        xml_file = arguments.right(arguments.length() - 3);
      else if (arguments.startsWith("-grade=", Qt::CaseInsensitive))
        report_grade = (arguments.right(arguments.length() - 7)).toInt();
      else if (arguments.startsWith("-package=", Qt::CaseInsensitive))
        package = arguments.right(arguments.length() - 9);
      else if(!arguments.startsWith("-"))
        xml_file = arguments;
    }

    QString report_name = QString::null;
    QString report_desc = QString::null;
    QString report_src  = QString::null;

    if(xml_file != "") {
        QFile file(xml_file);
        if(file.open( QIODevice::ReadOnly )) {
            QDomDocument doc;
            QString errMsg;
            int errLine, errCol;
            if(doc.setContent(&file, &errMsg, &errLine, &errCol)) {
                QDomElement root = doc.documentElement();
                if(root.tagName() == "report") {
                    for(QDomNode n = root.firstChild();
                            !n.isNull(); n = n.nextSibling() ) {
                        if(n.nodeName() == "name") {
                            report_name = n.firstChild().nodeValue();
                        } else if(n.nodeName() == "description") {
                            report_desc = n.firstChild().nodeValue();
                        }
                    }
                    report_src  = doc.toString();

                    if(report_name == "") {
                        out << "The document " << xml_file << " does not have a report name defined." << endl;
                    }
                } else {
                    out << "XML Document " << xml_file << " does not have root node of report." << endl;
                }
            } else {
                out << "Error parsing file " << xml_file << ": " << errMsg << " on line " << errLine << " column " << errCol << endl;
            }
        } else {
            out << "Could not open the specified file: " << xml_file << endl;
        }
    } else {
        out << "You must specify an XML file to load by using the -f= parameter." << endl;
    }

    if(report_name == "" || report_src == "") {
        // an error message already should have been displayed to the user
        exit(-1);
    }

    if (  (databaseURL != "") &&
          (username != "")    &&
          (passwd != "")          ) {
      QSqlDatabase db;

// Open the Database Driver
      db = databaseFromURL( databaseURL );
      if (!db.isValid())
      {
        out << "Could not load the specified database driver." << endl;
        exit(-1);
      }

//  Try to connect to the Database
      db.setUserName(username);
      db.setPassword(passwd);
      if (!db.open())
      {
        out << "Host=" << db.hostName() << ", Database=" << db.databaseName() << ", port=" << db.port() << endl;
        out << "Could not log into database.  System Error: "
            << db.lastError().text() << endl;
        exit(-1);
      }

      XSqlQuery().exec(getSqlFromTag("fmt05", db.driverName()));		// MANU

      // first we need to determine if there is already a report in the database of the same
      // name and if so then we will perform an update instead of an insert
      XSqlQuery qry;
      qry.prepare(getSqlFromTag("fmt09", db.driverName()));		// MANU
      qry.bindValue(":report_name", report_name);
      qry.bindValue(":report_grade", report_grade);
      qry.exec();
      XSqlQuery qry2;
      XSqlQuery query;
      if(qry.first()) {
        QString oldPackage;
        qry2.prepare(getSqlFromTag("fmt20", QSqlDatabase::database().driverName()));
        qry2.bindValue(":report_id", qry.value(0));
        qry2.exec();
        if(qry2.first())
          oldPackage = qry2.value("package").toString();

        if(package==oldPackage)
        {
          // update
          query.prepare(getSqlFromTag("fmt10", db.driverName()));		// MANU
          query.bindValue(":report_desc", report_desc);
          query.bindValue(":report_src", report_src);
          query.bindValue(":report_id", qry.value(0));
          query.bindValue(":report_name", report_name);
        }
        else
        {
          //move record
          QString tablename;
          qry2.prepare(getSqlFromTag("fmt22", QSqlDatabase::database().driverName()));
          if (!package.isEmpty())
            qry2.bindValue(":package", package);
          qry2.exec();
          if(qry2.first())
            tablename = qry2.value("tablename").toString();

          query.prepare(getSqlFromTag("fmt23", QSqlDatabase::database().driverName()).arg(tablename));
          query.bindValue(":report_id", qry.value(0));
          query.bindValue(":report_name", report_name);
          query.bindValue(":report_desc", report_desc);
          query.bindValue(":report_src", report_src);
          query.bindValue(":report_grade", report_grade);
        }
      } else {
        // insert
        QString tablename;
        qry2.prepare(getSqlFromTag("fmt22", QSqlDatabase::database().driverName()));
        if (!package.isEmpty())
          qry2.bindValue(":package", package);
        qry2.exec();
        if(qry2.first())
          tablename = qry2.value("tablename").toString();

        query.prepare(getSqlFromTag("fmt24", QSqlDatabase::database().driverName()).arg(tablename));
        query.bindValue(":report_name", report_name);
        query.bindValue(":report_desc", report_desc);
        query.bindValue(":report_src", report_src);
        query.bindValue(":report_grade", report_grade);
      }
      
      if(!query.exec()) {
          QSqlError err = query.lastError();
          out << "Error: " << err.driverText() << endl
              << "\t" << err.databaseText() << endl;
          exit(-1);
      }
      
    }
    else if (databaseURL == "")
      out << "You must specify a Database URL by using the -databaseURL= parameter." << endl;
    else if (username == "")
      out << "You must specify a Database Username by using the -username= parameter." << endl;
    else if (passwd == "")
      out << "You must specify a Database Password by using the -passwd= parameter." << endl;
  }
  else
    out << "Usage: import -databaseURL='$' -username='$' -passwd='$' -grade=# -package='$' -f='$'" << endl;
  return 0;
}
