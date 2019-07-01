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

#ifndef REPORTPROPERTIES_H
#define REPORTPROPERTIES_H

class QuerySourceList;

#include <QDialog>

#include "ui_reportproperties.h"

class ReportProperties : public QDialog, public Ui::ReportProperties
{
    Q_OBJECT

public:
    ReportProperties(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ReportProperties();

public slots:
    virtual QString getReportDescription();
    virtual QString getReportName();
    virtual QString getReportTitle();
    virtual void setReportDescription( QString str );
    virtual void setReportName( QString str );
    virtual void setReportTitle( QString str );
    virtual int getWatermarkOpacity();
    virtual void setWatermarkOpacity( int i );
    virtual void setWmFont( QFont fnt );
    virtual QFont getWmFont();
    virtual void SetUseBestWMFont( bool b );
    virtual bool getUseBestWmFont();
    virtual bool isWmTextStatic();
    virtual void setWmTextStatic( bool b );
    virtual QString getWmText();
    virtual void setWmText( QString str );
    virtual void setWmColumn( QString str );
    virtual QString getWmColumn();
    virtual void setWmQuery( QuerySourceList * qsl, QString query );
    virtual QString getWmQuery();
    virtual QString getBgColumn();
    virtual void setBgColumn( QString str );
    virtual QString getBgQuery();
    virtual void setBgQuery( QuerySourceList * qsl, QString query );
    virtual int getBgOpacity();
    virtual void setBgOpacity( int i );
    virtual bool isBgEnabled();
    virtual void setBgEnabled( bool b );
    virtual bool isBgStatic();
    virtual void setBgStatic( bool b );
    virtual QString getBgResizeMode();
    virtual void setBgResizeMode( QString m );
    virtual QString getBgImageData();
    virtual void setBgImageData( QString dat );
    virtual void setBgAlign( int f );
    virtual int getBgAlign();
    virtual int getBgBoundsX();
    virtual int getBgBoundsY();
    virtual int getBgBoundsWidth();
    virtual int getBgBoundsHeight();
    virtual void setBgBoundsX( int i );
    virtual void setBgBoundsY( int i );
    virtual void setBgBoundsWidth( int i );
    virtual void setBgBoundsHeight( int i );

protected:
    QString _uudata;

protected slots:
    virtual void languageChange();

    virtual void changeWmFont();
    virtual void sLoadBgImage();


};

#endif // REPORTPROPERTIES_H
