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

#ifndef EDITPREFERENCES_H
#define EDITPREFERENCES_H

#include <QDialog>

#include "ui_editpreferences.h"


class EditPreferences : public QDialog, public Ui::EditPreferences
{
    Q_OBJECT

public:
    EditPreferences(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~EditPreferences();

    QString selectedLanguage() {return _selectedLanguage;}

public slots:
    virtual void setGridSize( double x, double y );
    virtual double gridSizeX();
    virtual double gridSizeY();
    virtual bool showGrid();
    virtual bool snapGrid();
    virtual void setShowGrid( bool show );
    virtual void setSnapGrid( bool snap );
    virtual void setDefaultFont( QFont fnt );
    virtual QFont defaultFont();
    virtual void setPageSize(QString ps);
    virtual void setPageOrientation(QString po);

protected slots:
    virtual void languageChange();

    virtual void changeDefaultFont();
    virtual void selLanguage(QString sel);

private:
    QString _selectedLanguage;

};

#endif // EDITPREFERENCES_H
