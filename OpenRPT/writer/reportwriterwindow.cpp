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

#include "reportwriterwindow.h" // The Primary MDI window
#include "../wrtembed/reporthandler.h"       // The Report Window Child
#include <QDebug>

// common
#include <dbtools.h>
#include <xsqlquery.h>
#include <data.h>

// qt
#include <QSqlDatabase>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QAction>
#include <QEvent>
#include <QStatusBar>
#include <QPixmap>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QTimerEvent>
#include <QTranslator>
#include <QApplication>

// images
#include "../images/OpenReportsIcon.xpm" 
#include "builtinSqlFunctions.h"

//
// ReportWriterWindow
//
ReportWriterWindow::ReportWriterWindow()
  : QMainWindow() {
    
    setWindowTitle("OpenMFG: Report Writer");
    setWindowIcon(QPixmap(OpenReportsIcon_xpm));

    // add the workspace
    ws = new QMdiArea();

    setCentralWidget(ws);

    // setup the menubar
    fileExitAction = new QAction(tr("E&xit"), this);
    fileExitAction->setObjectName("file exit");
    fileExitAction->setShortcut(Qt::ALT+Qt::Key_F4);
    connect(fileExitAction, SIGNAL(triggered()), this, SLOT(appExit()));

    handler = new ReportHandler(this, "report handler");

#ifdef NODBSUPPORT
    handler->setNoDatabase(true);
#endif

    QAction * sepid = handler->populateMenuBar(menuBar(), fileExitAction);

    windowMenu = new QMenu(tr("&Windows"));
    //windowMenu->setCheckable(true);
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(sPrepareWindowMenu()));
    menuBar()->insertMenu(sepid, windowMenu);

    // setup the toolbar
    handler->docToolBars(this);

    setCaption();

    dbTimerId = startTimer(60000);

    handler->setParentWindow(ws);

    connect(handler, SIGNAL(dbOpenClosed()), this, SLOT(setCaption()));
    connect(handler, SIGNAL(messageChanged(const QString &)),
            statusBar(), SLOT(showMessage(const QString &)));
    connect(handler, SIGNAL(messageCleared()),
            statusBar(), SLOT(clearMessage()));
    handler->onWinChanged(NULL);
    connect(ws, SIGNAL(subWindowActivated(QMdiSubWindow*)), handler, SLOT(onWinChanged(QMdiSubWindow*)));
}

//
// Perform any cleanup action that needs to take place
//
ReportWriterWindow::~ReportWriterWindow() {
     // everything should be handled by Qt
}


//
// slot implementations
//
void ReportWriterWindow::appExit() {
    close();
}


//
// event handler methods
//

void ReportWriterWindow::timerEvent(QTimerEvent * e) {
    if(e->timerId() == dbTimerId) {
        QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::defaultConnection,false);
        if(db.isValid()) {
            QSqlQuery qry(getSqlFromTag("fmt07", db.driverName()));		// MANU

#if 0
            if(qry.first() == true) {
                // Nothing to do.  We were just creating a little traffic
                qDebug("Keep alive succeeded");
            } else {
                // I really don't care
                qDebug("Keep alive failed");
            }
#endif
        }
    }
}

void ReportWriterWindow::closeEvent(QCloseEvent * e) {
    QList<QMdiSubWindow *> wl = ws->subWindowList();
	qDebug() << "\n$$$$$$$$$$$ close event";
    for(int i = 0; i < wl.size(); i++)
    {
      if(wl.at(i) && !(wl.at(i)->close()))
      {
        e->ignore();
        return;
      }
    }
    e->accept();
}

void ReportWriterWindow::setCaption() {
    QString caption = QString("%1 %2 %3")
                          .arg(handler->name())
                          .arg(tr("Version"))
                          .arg(handler->version());

    QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::defaultConnection, false);
    if(db.isValid()) {
		XSqlQuery dbname;
        dbname.prepare( getSqlFromTag("fmt08", db.driverName()));		// MANU

        if ((dbname.isActive()) && (dbname.size())) {
            QString protocol;
            QString server;
            QString database;
            QString port;

            dbname.next();

            parseDatabaseURL((const QString &)OpenRPT::databaseURL,
                             protocol, server, database, port);

            caption = QString( tr("%1 - %2 on %3/%4 AS %5") )
                            .arg(caption)
                            .arg(dbname.value("metric_value").toString())
                            .arg(server)
                            .arg(database)
                            .arg(dbname.value("username").toString());
        }
    }

    QMainWindow::setWindowTitle(caption);
}

void ReportWriterWindow::sPrepareWindowMenu()
{
  windowMenu->clear();

  QAction * intCascadeid = windowMenu->addAction(tr("&Cascade"), ws, SLOT(cascadeSubWindows()));
  QAction * intTileid = windowMenu->addAction(tr("&Tile"), ws, SLOT(tileSubWindows()));

  windowMenu->addSeparator();

  int cnt = 0;
  QList<QMdiSubWindow *> windows = ws->subWindowList();
  for (int intCursor = 0; intCursor < windows.count(); intCursor++)
  {
    if(windows.at(intCursor)->isVisible())
    {
      QAction * intMenuid = windowMenu->addAction(windows.at(intCursor)->windowTitle(), windows.at(intCursor), SLOT(setFocus()));
      intMenuid->setChecked((ws->activeSubWindow() == windows.at(intCursor)));
      cnt++;
    }
  }

  if (cnt < 1)
  {
    intCascadeid->setEnabled(false);
    intTileid->setEnabled(false);
  }
}

void ReportWriterWindow::openReportFile(const QString &fileName)
{
  handler->fileOpen(fileName);
}

