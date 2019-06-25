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

#include <qapplication.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>

#include "graph.h"
#include "graphwindow.h"

#ifdef Q_WS_WIN
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
#ifdef XQ_WS_WIN
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(1, 1), &wsaData)) {
        qDebug("Error starting up Windows Socket system... libpq will not work.");
    }
#endif

    QApplication app(argc, argv);

    bool haveDB = false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    if(db.isValid()) {
        db.setDatabaseName("test");
        db.setUserName("cryan");
        db.setPassword("password");
        db.setHostName("localhost");
        if(db.open()) {
            haveDB = true;
        } else {
            QSqlError err = db.lastError();
            qDebug("Driver:   %s", err.driverText().toLatin1().data());
            qDebug("Database: %s", err.databaseText().toLatin1().data());
            qDebug("Could not make connection to database: sql query will be disabled");
        }
    } else {
        qDebug("Could not load the database driver: sql query will be disabled");
    }

    GraphWindow gw;
    gw.init(haveDB);
    gw.show();

    int ret = app.exec();

#ifdef XQ_WS_WIN
    WSACleanup();
#endif

    return ret;
}

