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

#ifndef GRAPHEDITOR_H
#define GRAPHEDITOR_H

#include <QDialog>
#include <QList>

#include "ui_grapheditor.h"
#include "parsexmlutils.h"

class GraphEditor : public QDialog, public Ui::GraphEditor
{
    Q_OBJECT

public:
    GraphEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~GraphEditor();

public slots:
    virtual void _btnBaseFont_clicked();
    virtual void setBaseFont( QFont fnt );
    virtual QFont getBaseFont();
    virtual void _btnTitleFont_clicked();
    virtual QFont getTitleFont();
    virtual void setTitleFont( QFont fnt );
    virtual bool getUseTitleFont();
    virtual void setUseTitleFont( bool yes );
    virtual QString getTitle();
    virtual void setTitle( QString str );
    virtual QString getDataTitle();
    virtual void setDataTitle( QString str );
    virtual bool getUseDataTitleFont();
    virtual void setUseDataTitleFont( bool yes );
    virtual QFont getDataTitleFont();
    virtual void setDataTitleFont( QFont fnt );
    virtual void _btnDataTitleFont_clicked();
    virtual QString getDataColumn();
    virtual void setDataColumn( QString str );
    virtual bool getUseDataFont();
    virtual void setUseDataFont( bool yes );
    virtual void _btnDataFont_clicked();
    virtual QFont getDataFont();
    virtual void setDataFont( QFont fnt );
    virtual QString getValueTitle();
    virtual void setValueTitle( QString str );
    virtual bool getUseValueTitleFont();
    virtual void setUseValueTitleFont( bool yes );
    virtual void _btnValueTitleFont_clicked();
    virtual QFont getValueTitleFont();
    virtual void setValueTitleFont( QFont fnt );
    virtual void _btnValueFont_clicked();
    virtual QFont getValueFont();
    virtual void setValueFont( QFont fnt );
    virtual bool getUseValueFont();
    virtual void setUseValueFont( bool yes );
    virtual int getHPadding();
    virtual void setHPadding( int hPadding );
    virtual int getVPadding();
    virtual void setVPadding( int vPadding );
    virtual bool getAutoMinMax();
    virtual void setAutoMinMax( bool yes );
    virtual double getMinValue();
    virtual double getMaxValue();
    virtual void setMaxValue( double val );
    virtual void setMinValue( double val );
    virtual void _btnNewSeries_clicked();
    virtual void _btnRemoveSeries_clicked();
    virtual void _btnEditColors_clicked();
    virtual void _cbSeriesStyleBars_toggled( bool yes );
    virtual void _cbSeriesStyleLines_toggled( bool yes );
    virtual void _cbSeriesStylePoints_toggled( bool yes );
    virtual void _cbColors_activated( const QString & str );
    virtual void _leSeriesColumn_textChanged( const QString & str );
    virtual void _leSeriesName_textChanged( const QString & str );
    virtual void _cbSeries_activated( const QString & str );
    virtual QList<ORSeriesData*>& getSeriesList();
    virtual void setColorMap( QMap<QString, QColor> * cmap );

protected:
    QMap<QString,QColor>* _colorMap;
    ORSeriesData * _seriesData;
    QList<ORSeriesData*> _seriesList;

protected slots:
    virtual void languageChange();

};

#endif // GRAPHEDITOR_H
