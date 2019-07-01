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

#ifndef dbTools_h
#define dbTools_h

#include <QString>
#include <QSqlDatabase>

QString normalizeProtocol(QString protocol);
void parseDatabaseURL(const QString & /* pDatabaseURL */,
                            QString & /* pProtocol    */,
                            QString & /* pServer      */,
                            QString & /* pDatabase    */,
                            QString & /* pPort        */);

void buildDatabaseURL(      QString & /* pTarget      */,
                      const QString & /* pProtocol    */,
                      const QString & /* pServer      */,
                      const QString & /* pDatabase    */,
                      const QString & /* pPort        */);

QSqlDatabase databaseFromURL( const QString& databaseURL );

#endif

