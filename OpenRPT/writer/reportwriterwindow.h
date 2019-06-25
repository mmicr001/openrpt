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

#ifndef __REPORTWRITERWINDOW_H__
#define __REPORTWRITERWINDOW_H__

#include <QMainWindow>
#include <QTimerEvent>
#include <QCloseEvent>

//
// Prototypes
//
class QMdiArea;
class QAction;
class ReportHandler;
class QMenu;
class QString;

//
// Class: ReportWriterWindow
//
class ReportWriterWindow : public QMainWindow {
    Q_OBJECT
    public:
        ReportWriterWindow();
        ~ReportWriterWindow();
		

    public slots:
        virtual void setCaption();
        virtual void openReportFile(const QString &);

    protected:
        virtual void closeEvent(QCloseEvent*);
        virtual void timerEvent(QTimerEvent*);

    private:
        QMdiArea * ws;
        int dbTimerId;

        QAction * fileExitAction;

        ReportHandler * handler;

        QMenu *windowMenu;

    private slots:
        void appExit();
        void sPrepareWindowMenu();
};

#endif

