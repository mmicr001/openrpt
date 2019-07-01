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

#include "dbtools.h"

#include <QHash>
#include <QUrl>

void parseDatabaseURL(const QString &pDatabaseURL, QString & pProtocol, QString &pServer, QString &pDatabase, QString &pPort)
{
  int location;

  QUrl url(pDatabaseURL);
  pProtocol = url.scheme();
  pServer = url.host();
  pDatabase = url.path();
  if(pDatabase.startsWith("/"))
    pDatabase = pDatabase.mid(1);
  int port = url.port();
  if(port <= 0)
  {
    // If the port is not specified it may be the old style so lets check
    // for it in the database path like we used to do
    location = pDatabase.indexOf(":");
    if(-1 != location)
    {
      port = pDatabase.right(pDatabase.length() - location - 1).toInt();
      pDatabase = pDatabase.left(location);
    }
  }
  if(port <= 0)
    port = 5432;
  pPort = QString().setNum(port);
}

void buildDatabaseURL(QString &pTarget, const QString & pProtocol, const QString &pServer, const QString &pDatabase, const QString &pPort)
{
  pTarget = pProtocol + "://" + pServer + ":" + pPort + "/" + pDatabase;
}

QString normalizeProtocol(QString protocol)
{
  static QHash<QString, QString> map;
  if (map.isEmpty()) {
    map["db2"]     = "QDB2";
    map["ibase"]   = "QIBASE";
    map["mysql"]   = "QMYSQL";
    map["odbc"]    = "QODBC";
    map["oracle"]  = "QOCI";
    map["pgsql"]   = "QPSQL";
    map["psql"]    = "QPSQL";
    map["sqlite"]  = "QSQLITE";
    map["sqlite2"] = "QSQLITE2";
    map["sybase"]  = "QTDS";
  }

  return map.contains(protocol) ? map.value(protocol)
                                : protocol.toUpper();
}

QSqlDatabase databaseFromURL( const QString& databaseURL )
{
  QString protocol;
  QString hostName;
  QString dbName;
  QString port;

  parseDatabaseURL( databaseURL, protocol, hostName, dbName, port );
  QSqlDatabase db = QSqlDatabase::addDatabase(normalizeProtocol(protocol));
  if ( db.isValid() )
  {
    db.setDatabaseName(dbName);
    db.setHostName(hostName);
    // Check if port was provided. If not, let Qt decide, it knows default values.
    bool ok;
    int iport = port.toInt( &ok );
    if ( ok )
      db.setPort( iport );
  }
  return db;
}
