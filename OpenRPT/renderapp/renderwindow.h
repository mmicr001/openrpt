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

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QMainWindow>
#include <QMap>

#include "tmp/ui_renderwindow.h"

class RenderWindow : public QMainWindow, public Ui::RenderWindow
{
    Q_OBJECT

public:
    RenderWindow(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~RenderWindow();

    QString _printerName;
    bool _autoPrint;                //AUTOPRINT

    virtual ParameterList getParameterList();
    static QString name();

public slots:
    virtual void helpRefGuide();
    virtual void helpAbout();
    virtual void fileOpen();
    virtual void fileOpen( const QString & filename );
    virtual void fileLoad();
    virtual void fileLoad( const QString & reportname );
    virtual void filePreview( int numCopies = 1 );
    virtual void filePrint( int numCopies = 1 );
    virtual void filePrintToPDF();
    // BVI::Sednacom
    // declare the new member
    virtual void filePrintToPDF( QString & pdfFileName );
    // BVI::Sednacom
    virtual void fileExit();
    virtual void updateParam( const QString & name, const QVariant & value, bool active );
    virtual void setDocument( const QDomDocument & doc);

protected:
    QMap<QString, QList<QPair<QString,QString> > > _lists;
    QDomDocument _doc;
    QMap<QString,QVariant> _params;

protected slots:
    virtual void languageChange();

    virtual void sAdd();
    virtual void sEdit();
    virtual void sDelete();
    virtual void sSelectionChanged();
    virtual void sList();

private:
    void print (bool showPreview, int numCopies);
};

#endif // RENDERWINDOW_H
